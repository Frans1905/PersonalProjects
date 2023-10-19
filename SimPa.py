
def print_pa(seq, transition_list, curr_state, stack, states_list, accept_state, alphabet, ret):

    if(ret == -1):
        return ret
    
    print(curr_state, end="")
    print("#", end="")
    if (not stack):
        print("$", end="")
    else:
        for el in reversed(stack):
            print(el, end="")
    print("|", end="")
    if (seq):
        sign = seq.pop(0)
    else:
        sign = "$"
    if (stack):
        symbol = stack.pop()
    else:
        symbol = "$"

    check = 0
    for comb in transition_list:
        transition_left = comb.split("->")[0]
        transition_right = comb.split("->")[1]
        transition_left = transition_left.split(",")
        if (transition_left[0] == curr_state and (transition_left[1] == sign or transition_left[1] == "$") and transition_left[2] == symbol):
            check = 1
            if (transition_left[1] == "$"):
                if (curr_state == accept_state and sign == "$"):
                    break
                seq.insert(0, sign)
            next_state = transition_right.split(",")[0]
            next_symbol = transition_right.split(",")[1]
            next_stack = stack_add(stack, next_symbol, symbol)
            ret = print_pa(seq, transition_list, next_state, stack, states_list, accept_state, alphabet, ret)
            if (ret == -1):
                break;
    
    if (check == 0 and sign != "$"):
        ret = -1
        print("fail|0")
        
    elif (curr_state == accept_state and sign == "$"):
        ret = 1
    
    return ret

    

def stack_add(stack, next_symbol, symbol):
    
    if(len(next_symbol) == 1 and next_symbol != "$"):
        stack.append(next_symbol)
        
    elif(next_symbol != "$"):
        for c in reversed(next_symbol):
            stack.append(c)
            
    return stack


seq_list = input().split("|")
states_list = input().split(",")
alphabet = input().split(",")
alphabet.append("$")
symbol_list = input().split(",")
accept_state = input()
start_state = input()
start_symbol = input()
transition_list = []
seq = input()

while(seq != "") :
    try:
        transition_list.append(seq)
        seq = input()
    except EOFError as e:
        break

for i in range(len(seq_list)):
    seq = seq_list[i].split(",")
    stack = []
    stack.append(start_symbol)
    ret = 0
    ret = print_pa(seq, transition_list, start_state, stack, states_list, accept_state, alphabet, ret)
    if (ret != -1):
        print(ret)



