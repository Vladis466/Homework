import os, sys, stat, subproces, time, shlex

def sp_os(path):
    files = os.listdir(path)
    
    files.extend('. ..'.split())

    sorted_files = []
