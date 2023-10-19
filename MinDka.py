

def minimise_dka(states_list, alphabet, transition_matrix, accept_states, start_state):
    
    state_matrix = [["#" for x in range(len(states_list))] for y in range(len(states_list))]
    for state in accept_states:
        if (state in states_list):
            index = states_list.index(state)
            for i in range(len(states_list)):
                if (states_list[index] != states_list[i] and states_list[i] not in accept_states):
                    state_matrix[index][i] = "x"
                    state_matrix[i][index] = "x"
                
    for i in range(len(states_list)):
        for j in range(0, i):
            if (i != j and state_matrix[i][j] != "x"):
                for k in range(len(alphabet)):
                    first_state = transition_matrix[i][k]
                    second_state = transition_matrix[j][k]
                    index1 = states_list.index(first_state)
                    index2 = states_list.index(second_state)
                    if (state_matrix[index1][index2] == "x"):
                        state_matrix = mark_list(state_matrix[i][j], state_matrix, states_list)
                        state_matrix[i][j] = "x"
                        state_matrix[j][i] = "x"
                        break
                        
                    else:
                        if (first_state != second_state):
                            state_matrix = link_pair(i, j, k, state_matrix, transition_matrix, states_list)


    states_list = remove_hashtags(states_list)

    (minimised_states_list, minimised_transition_matrix, minimised_accept_states, minimised_start_state) = fetch_minimised_machine(state_matrix, transition_matrix, states_list, accept_states, start_state)
           

            
    return (minimised_states_list, minimised_transition_matrix, minimised_accept_states, minimised_start_state)
    
def remove_hashtags(lst):
    new_lst = []
    for el in lst:
        if (el != "#"):
            new_lst.append(el)
    return new_lst

def fetch_minimised_machine(state_matrix, transition_matrix, states_list, accept_states, start_state):
    remove_states = []
    for i in range(len(states_list)):
        for j in range(0, i):
            if (state_matrix[i][j] != "x"):
                index_primary = min(i, j)
                index_secondary = max(i, j)
                if (states_list[index_secondary] not in remove_states):
                    (transition_matrix, accept_states, start_state) = switch_secondary(states_list[index_primary], states_list[index_secondary], transition_matrix, accept_states, start_state)
                    remove_states.append(states_list[index_secondary])
    new_states_list = []
    for state in states_list:
        if (state not in remove_states):
            new_states_list.append(state)
    transition_matrix = create_new_transition_matrix(transition_matrix, new_states_list, states_list)

    minimised_accept_states = []
    for state in new_states_list:
        if (state in accept_states):
            minimised_accept_states.append(state)
            
    return (new_states_list, transition_matrix, minimised_accept_states, start_state)    

def create_new_transition_matrix(transition_matrix, new_states_list, old_states_list):
    new_transition_matrix = [["#" for x in range(len(transition_matrix[0]))] for y in range(len(new_states_list))]
    k = 0
    for i in range(len(old_states_list)):
        if(old_states_list[i] in new_states_list):
            for j in range(len(transition_matrix[i])):
                new_transition_matrix[k][j] = transition_matrix[i][j]
            k += 1
    return new_transition_matrix
    
def switch_secondary(primary, secondary, transition_matrix, accept_states, start_state):

    for i in range(len(transition_matrix)):
        for j in range(len(transition_matrix[i])):
            if (transition_matrix[i][j] == secondary):
                transition_matrix[i][j] = primary
                
    for i in range(len(accept_states)):
        if (accept_states[i] == secondary):
            accept_states[i] = primary

    if (start_state == secondary):
        start_state = primary
        
    return transition_matrix, accept_states, start_state


def link_pair(i, j, k, state_matrix, transition_matrix, states_list):
    
    first_state = transition_matrix[i][k]
    second_state = transition_matrix[j][k]
    link_index1 = states_list.index(first_state)
    link_index2 = states_list.index(second_state)
    first_link_state = states_list[i]
    second_link_state = states_list[j]
    if ((first_state == first_link_state and second_state == second_link_state) or (first_state == second_link_state and second_state == first_link_state)):
        return state_matrix
    link_string = first_link_state + ',' + second_link_state
    
    if (state_matrix[link_index1][link_index2] != "#"):
        old_string = state_matrix[link_index1][link_index2]
        link_string = old_string + ':' + link_string
        
    state_matrix[link_index1][link_index2] = link_string
    state_matrix[link_index2][link_index1] = link_string
    return state_matrix
                        
def mark_list(seq, state_matrix, states_list):
    if (seq != "#" and seq != "x"):
        seq = seq.split(":")
        for pair in seq:
            pair = pair.split(",")
            index1 = states_list.index(pair[0])
            index2 = states_list.index(pair[1])
            state_matrix = mark_list(state_matrix[index1][index2], state_matrix, states_list)
            state_matrix[index1][index2] = "x"
            state_matrix[index2][index1] = "x"
    return state_matrix


def remove_unattainable(states_list, alphabet, transition_matrix, start_state):
    
    reachable_states = ["#" for x in range(len(states_list))]
    reachable_states[0] = start_state
    i = 0
    
    while(i < len(states_list) and reachable_states[i] != "#"):
        curr_state = reachable_states[i]
        current_index = states_list.index(curr_state)
        for j in range(len(alphabet)):
            if (transition_matrix[current_index][j] != "#" and transition_matrix[current_index][j] not in reachable_states):
                for k in range(len(reachable_states)):
                    if (reachable_states[k] == "#"):
                        transition_matrix[current_index][j] = transition_matrix[current_index][j].replace("\r", "")
                        reachable_states[k] = transition_matrix[current_index][j]
                        break

        i = i + 1

    for i in range(len(reachable_states)):
        if (i < len(reachable_states) and reachable_states[i] == "#"):
            del reachable_states[i]
            
    reachable_states.sort()
    
    new_transition_matrix = [["#" for x in range(len(alphabet))] for y in range(len(reachable_states))]
    i = 0
    for state in reachable_states:
        if (state != "#"):
            index = states_list.index(state)
            for j in range(len(alphabet)):
                new_transition_matrix[i][j] = transition_matrix[index][j]
            i = i + 1
        
    return (reachable_states, new_transition_matrix)


def print_machine(states_list, alphabet, accept_states, start_state, transition_matrix):

    if (states_list):
        for i in range(len(states_list)):
            if (i == len(states_list) - 1):
                print(states_list[i])
            else:
                print(states_list[i], end = ",")
    else:
        print("")

    for i in range(len(alphabet)):
        if (i == len(alphabet) - 1):
            print(alphabet[i])
        else:
            print(alphabet[i], end = ",")

    if (accept_states):
        for i in range(len(accept_states)):  
            if (i == len(accept_states) - 1):
                print(accept_states[i])
            else:
                print(accept_states[i], end = ",")
    else:
        print("")
        
    print(start_state)

    for i in range(len(states_list)):
        for j in range(len(alphabet)):
            if (transition_matrix[i][j] != "#"):
                print(states_list[i], end = ",")
                print(alphabet[j], end = "->")
                print(transition_matrix[i][j])
    
    
        
states_list = input().split(",")
alphabet = input().split(",")
accept_states = input().split(",")
start_state = input()

transition_matrix = [["#" for x in range(len(alphabet))] for y in range(len(states_list))]
for i in range(len(states_list)) :
    for j in range(len(alphabet)) :
        transition_matrix[i][j] = "#"

seq = input()
while(seq != "") :
    try:
        seq_split = seq.split("->")
        funct = seq_split[0].split(",")
        transition_state = seq_split[1]
        for i in range(len(states_list)):
            for j in range(len(alphabet)):
                if (funct[0] == states_list[i] and funct[1] == alphabet[j]):
                    transition_matrix[i][j] = transition_state
        seq = input()
    except EOFError as e:
        break

(states_list, transition_matrix) = remove_unattainable(states_list, alphabet, transition_matrix, start_state)

for i in range(len(accept_states)):
    if (i < len(accept_states) and accept_states[i] not in states_list):
        del accept_states[i]
        i -= 1

(states_list, transition_matrix, accept_states, start_state) = minimise_dka(states_list, alphabet, transition_matrix, accept_states, start_state)

print_machine(states_list, alphabet, accept_states, start_state, transition_matrix)
        
