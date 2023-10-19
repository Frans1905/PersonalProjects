from sys import stdin


def print_nda(stack, transition_matrix, current_states, states_list, alphabet):

    check = 1
    while (check):
        check = 0
        if(not current_states):
            break
        for i in range(len(current_states)):
            index = states_list.index(current_states[i])
            if (transition_matrix[index][len(alphabet) - 1] != "#"):
                transition_states_split = transition_matrix[index][len(alphabet) - 1].split(",")
                for j in range(len(transition_states_split)):
                    if (transition_states_split[j] not in current_states):
                        current_states.append(transition_states_split[j])
                        check = 1

                        
    if (current_states):
        current_states.sort()
        for i in range(len(current_states)):
            if (i < len(current_states) - 1):
                print(current_states[i], end = "")
                print(",", end = "")
            else:
                print(current_states[i], end = "")
    else:
        print("#", end = "")
    

    next_states = []
    transition_check = 0
    if (stack):
        print("|", end = "")
        el = stack.pop()
        for i in range(len(states_list)):
             for j in range(len(alphabet)):
                 if (states_list[i] in current_states and el == alphabet[j]):
                     if (transition_matrix[i][j] != "#"):
                         transition_states_split = transition_matrix[i][j].split(",")
                         for i in range(len(transition_states_split)):
                             if (transition_states_split[i] not in next_states):
                                 next_states.append(transition_states_split[i])
                                 transition_check = 1
                    
    else:
        return
    check = 1
    while (check):
        check = 0
        if(not current_states):
            break
        for i in range(len(current_states)):
            index = states_list.index(current_states[i])
            if (transition_matrix[index][len(alphabet) - 1] != "#"):
                transition_states_split = transition_matrix[index][len(alphabet) - 1].split(",")
                for j in range(len(transition_states_split)):
                    if (transition_states_split[j] not in current_states and transition_states_split[j] not in next_states):
                        next_states.append(transition_states_split[j])
                        check = 1


    print_nda(stack, transition_matrix, next_states, states_list, alphabet)
                
            
    return


seq_list = input().split("|")
states_list = input().split(",")
alphabet = input().split(",")
alphabet.append("$")
accept_states = input()
start_state = input().split(",")
transition_matrix = [["#" for x in range(len(alphabet))] for y in range(len(states_list))]
for i in range(len(states_list)) :
    for j in range(len(alphabet)) :
        transition_matrix[i][j] = "#"

seq = input()
while(seq != "") :
    seq_split = seq.split("->")
    funct = seq_split[0].split(",")
    transition_states = seq_split[1]
    for i in range(len(states_list)):
        for j in range(len(alphabet)):
            if (funct[0] == states_list[i] and funct[1] == alphabet[j]):
                transition_matrix[i][j] = transition_states
    try:
        seq = input()
    except EOFError:
        seq = ""

for i in range(len(seq_list)):
    seq = seq_list[i].split(",")
    stack = []
    for i in range(len(seq)):
        stack.append(seq[len(seq) - 1 - i])
    print_nda(stack, transition_matrix, start_state, states_list, alphabet)
    print("")
