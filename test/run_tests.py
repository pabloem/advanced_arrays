#!/usr/bin/env python

from datetime import datetime as dt
import subprocess
import re
from os import listdir
from os.path import isfile

class AdvancedArraysTest:
    version = "0.1"
    av_tests = ["lit_hash_extensive.cc","ext_arr_random_shgr.cc",
                "ext_arr_vanilla_test.cc","ext_arr_test_shrink.cc",
                "ext_arr_pushpop.cc"]

    def __init__(self,outfile,errfile,mast_file = 'output_masterfile'):
        self.of = open(outfile,'w')
        self.ef = open(errfile, 'w')
        self.my_files = list()
        self.my_files.append(outfile)
        self.my_files.append(errfile)
        self.my_files.append(mast_file)
        pass

    def write_header(self):
        self.output("===============================")
        self.output("ADVANCED ARRAYS TEST SUITE v"+self.version)
        self.output("===============================")
        self.output("Time: "+str(dt.now()))
        self.output("===============================")
        self.output("STARTING TEST SUITE NOW")
        self.output("===============================\n")
        return 1

    def remove_prev(self):
        err_f = re.compile("stderr_[0-9][0-9]-[0-9][0-9]_[0-9][0-9]:[0-9][0-9]:[0-9][0-9]")
        out_f = re.compile("output_[0-9][0-9]-[0-9][0-9]_[0-9][0-9]:[0-9][0-9]:[0-9][0-9]")
        files = [f for f in listdir('.') if isfile(f)
                                         if err_f.match(f) 
                                            or out_f.match(f) 
                                            or f == 'output_diffs'
                                         if f not in self.my_files]
        self.output("Removing older files...")
        for fname in files:
            self.output("Removing "+fname)
            subprocess.call(["rm",fname])
        return 1

    def output(self,out_str,err = False):
        self.of.write(out_str+"\n")
        self.of.flush()
        print(out_str)
        if err: 
            self.ef.write(out_str+"\n")
            self.ef.flush()
        return 1
        
    def run_tests(self):
        self.write_header()

        files = [f for f in listdir('.') if isfile(f) 
                                         if f in AdvancedArraysTest.av_tests]
        for fname in files:
            self.output("FILE: "+fname,err=True)
            self.output("Compiling...")
            outp = subprocess.call(["g++",fname,"-g"])
            if outp != 0: 
                self.output("ERROR in compilation of "+fname,err=True)
                return "ERROR compiling "+fname
            self.output("Running...")
            outp = subprocess.call(["./a.out"], stdout=self.of, stderr=self.ef)
        self.of.close()
        self.ef.close()
        return "Ran succesfully"
        
    def match_diffs(self):
        output_file = self.my_files[0]
        master_file = self.my_files[2]
        print("Matching diffs...")
        try:
            subprocess.check_output(["diff", 
                                            "-I","Removing\|Time\|0x[0-9a-f]*",
                                            master_file, output_file])
        except subprocess.CalledProcessError, e:
            print("=========================")
            print("ERRORS HAVE BEEN FOUND ")
            print("REVIEW file output_diff and "+output_file)
            print("=========================")
            errs = open("output_diffs",'w')
            errs.write(e.output)
            errs.close()
            return 1
        return 0
        


now = dt.now()

output_name = "output_"+ now.strftime("%m-%d_%H:%M:%S")
errors_name = "stderr_"+ now.strftime("%m-%d_%H:%M:%S")

tester = AdvancedArraysTest(output_name,errors_name)

tester.remove_prev()
res = tester.run_tests()
tester.match_diffs()

