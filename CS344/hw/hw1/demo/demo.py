import os, shlex, subprocess, time

def ls_sp:
    command = "ls-lartn"
    command_parsed = shlex.split(command)
    result = subprocess.Popen(command_parsed, stdout=subprocess.PIPE)
    
    output = result.stdout.readlines()
    print(output)
    
    for i in output:
        print(i)
    

if __name__ = '__main__':
    ls_sp()


#we can call this as if its our own ls. Dis program does something.
