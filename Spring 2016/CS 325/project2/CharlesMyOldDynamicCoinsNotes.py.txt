cntmem = [[0 for x in range(1000)] for x in range(1000)] 

def cnt(arr, size, target):
    if target == 0:
        return 1            #only 1 way of making 0 with n amt of coins. Use 0 coins
    if target < 0:          
        return 0            # if target is less than 0, no solution
    if size < 1:
        return 0            # If size of array 0 or below, no coins --> no solution
    
    # solving subproblems. In order for the program to run faster, use a 2d memory back to store the results of combinations
    # That way they do not get solved again as we can just plug them in quickly. 
    if (cntmem[size-1][target] != 0):
        return cntmem[size-1][target]       
    
    result = cnt(arr, size-1, target) + cnt(arr, size, target - arr[size-1])
    cntmem[size-1][target] = result
    return result
# left: will continue branching with 1 less value of the array but the same target.
# right: continually subtracts the greatest value in the array from the target. Due to the recursive structure, this simulates
# using one more of the biggest coin possible each time and seeing if you can reach the target. Ultimately, most of the magic lies
# in the right side of this statement.


# The goal of this program is to find all the combinations of numbers('coins') that will make the target

n = map(int,raw_input().split(' '))  # n[0] is the target, n[1] size of the array


numarr = map(int,raw_input().split())
numarr.sort()
dnum = numarr[0]
print cnt(numarr, n[1], n[0])



    


