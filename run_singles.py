#use python run_shells.py ./aff.c 16 1000 500
import sys
import subprocess
import os
import time

def main():
    if(len(sys.argv) != 6):
        print("Error: format is [python time_test.py num_tests program num_procs loop_length num_loops]")
        sys.exit(1)

    num_tests = sys.argv[1]
    cmd = " ".join(sys.argv[2:])
    
    print("num_tests: "+num_tests)
    print("cmd: "+cmd)
    print("starting tests")



    if os.path.exists("output.txt"):
        os.remove("output.txt")

    for i in range(int(num_tests)): 
        subprocess.check_output(cmd, shell=True)
    
    f = open("output.txt", "r")
    print(f)
    #print(f.read())


    total_real = 0
    total_user = 0
    total_sys = 0

    for x in f:
        print(x)
        try:
            splitt = x.split("\t")
            print(splitt)
            cat = splitt[0]
            time = splitt[1]
            print("cat: "+cat)
            print("time: "+time)
            
            time_split = time[2:7]

            if cat == "real":
                print("time: "+ time_split)
                total_real += int(time_split)
            elif cat == "user":
                print("time: "+ time_split)
                total_user += int(time_split)
            elif cat == "sys":
                print("time: "+ time_split)
                total_sys += int(time_split)

            else:
                print("other cat")
        
        except:
            print("skip empty line")


        ##############################
        print("total real: "+total_real)

        print("total user: "+total_user)

        print("total sys: "+total_sys)


if __name__ == "__main__":
    main()
