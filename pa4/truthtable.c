#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Linked List implementation of Digital Logic Board.
    Input must be sorted.
*/

int arr_vars[3000][3000];

typedef struct num {

    int number;

    struct num *next;

}num;

typedef struct gate{

    int code;

    num *input;

    num *temp_vars;

    int output;

    struct gate *next;

}gate;

    /*

    Gate | Code

    PASS | 1
    NOT | 2
    AND | 3
    OR| 4
    NAND | 5
    NOR | 6
    XOR | 7
    DECODER | 8
    MULTIPLEXER | 9

    */

typedef struct node {

    char* var_name;  //name for variable; used temporarily

    struct node *next;

}node;

void binary(int bits[], int length, int t, int c);


int main(int argc, char** argv){

    FILE *file = fopen(argv[1], "r");

    char input_directive[3000];

    fgets(input_directive,3000,file); //reads entire line

    node *vars = (node *) malloc(sizeof(node));

    char* token;

    int firstIteration = 1; int secondIteration = 1;

    token = strtok(input_directive, " "); //first token in input line INPUT

    while(token != NULL){

        if(firstIteration) firstIteration--;
        else if(secondIteration){

            secondIteration--;
            vars->var_name = token;
            vars->next = NULL;

        }
        else{

            node *ptr = vars;

            while(ptr->next != NULL){
                ptr = ptr->next;
            }

            node *newNode = malloc(sizeof(node));

            newNode->var_name = token; newNode->next = NULL;

            ptr->next = newNode;

        }

        token = strtok(NULL, " ");
    } //vars is all input vars

    char output_directive[3000];

    fgets(output_directive,3000,file);

    node *out = (node*) malloc(sizeof(node));

    char* token_part_two;

    firstIteration = 1; secondIteration = 1;

    token_part_two = strtok(output_directive, " "); //first token of output line OUTPUT

    while(token != NULL){

        if(firstIteration) firstIteration--;
        else if(secondIteration){

            secondIteration--;
            out->var_name = token_part_two;
            out->next = NULL;

        }
        else{

            node *ptr = out;

            while(ptr->next != NULL){
                ptr = ptr->next;
            }

            node *newNode = malloc(sizeof(node));

            newNode->var_name = token_part_two; newNode->next = NULL;

            ptr->next = newNode;

        }

        token_part_two = strtok(NULL, " ");
    } //out is all output variables

    node * temp_vars = (node*) malloc(sizeof(node));
    temp_vars->var_name = " "; temp_vars->next = NULL;
    char current_directive[3000];

    gate *board = (gate*) malloc(sizeof(gate));
    board->code = 0;

    while(fgets(current_directive, 3000, file) != NULL){

        int current_gate_code;

        num * current_input_list = (num*) malloc(sizeof(num)); //List of inputs
        current_input_list->number = 0; //initial value, ignore
        current_input_list->next = NULL;

        num * current_temp_vars = (num*) malloc(sizeof(num)); //list of any temporary input variables
        current_temp_vars->number = 0; //ignore
        current_temp_vars->next = NULL;

        int current_output;

        //ABOVE: Structure variable initialization for current Logic Gate

        int ito = 0; //Boolean value that signifies a switch from input to output

        int current_input_is_temp = 0; //Boolean value that signifies if the current input is a temp var

        char *tok;

        tok = strtok(current_directive, " ");

        firstIteration = 1; //Boolean value that signifies if the loop is in the first iteration

        while(tok != NULL){ //analysis of the current gate directive

            if(ito){ //initializes output
                node *out_ptr = out;

                int out_c = 0;

                while(out_ptr != NULL){
                    if(strcmp(tok, out_ptr->var_name) == 0){ current_output = out_c; break; }

                    if(out_ptr->next == NULL){
                        current_output = 0; current_output--; out_c = 0;
                        node * temp_ptr = temp_vars;
                        if(strcmp(" ", temp_ptr->var_name) == 0){ temp_ptr->var_name = tok; }
                        else{
                            while(temp_ptr->next != NULL){ out_c--; temp_ptr = temp_ptr->next; }
                            temp_ptr->next = (node*) malloc(sizeof(num));
                            temp_ptr->next->var_name = tok; temp_ptr->next->next = NULL;
                        }

                        break;
                    }

                    out_ptr = out_ptr->next;
                }

                tok = strtok(NULL, " ");
                continue;
            }

            if(tok[0] == ':'){ ito = 1; tok = strtok(NULL, " "); continue; }

            if(firstIteration){ //initializes gate code / type on first iteration of loop
                firstIteration = 0;
                if(tok[0] == 'P') current_gate_code = 1;
                if(tok[0] == 'A') current_gate_code = 3;
                if(tok[0] == 'O') current_gate_code = 4;
                if(tok[0] == 'X') current_gate_code = 7;
                if(tok[0] == 'N'){
                    if(tok[2] == 'T') current_gate_code = 2;
                    if(tok[2] == 'N') current_gate_code = 5;
                    if(tok[2] == 'R') current_gate_code = 6;
                }
                if(tok[0] == 'M' || tok[0] == 'D'){
                    //finish Multiplexer and Decoder implementation
                    //maybe make a function for each
                    //maybe make a new structure for decoder since it has more than 1 input
                    //do everything for each in here then break to end loop
                    /*
                        Set gate codes 8 and 9 for decoder and multiplexer, break loop, when executing
                        program, jump to multiplexer/decoder method when gate code is detected
                    */
                   }
            }
            else{  //initializes list of inputs
                node *pter = vars->next; //pointer to variable list

                int var_c = 0;

                while(pter != NULL){

                    if(strcmp(tok, pter->var_name) == 0) {

                        num *pter2 = current_input_list;
                        while(pter2->next != NULL){
                            pter2 = pter2->next;
                        } //pter2 is last node of current input list

                        pter2->next = (num*) malloc(sizeof(num));
                        pter2->next->number = var_c; pter2->next->next = NULL;

                        break;
                    }

                    if(pter->next == NULL){ //must be a temp variable if this point is reached
                        num *pter2 = current_input_list;
                        while(pter2->next != NULL){
                            pter2 = pter2->next;
                        } //pter2 is last node of current input list

                        pter2->next = (num*) malloc(sizeof(num));
                        pter2->next->number = 0; pter2->next->number--; pter2->next->next = NULL;
                        current_input_is_temp = 1;
                    }

                    var_c++;
                    pter = pter->next;

                }

                if(current_input_is_temp){

                    current_input_is_temp = 0;

                    node * pter2 = temp_vars->next; //support of variable used between input and output

                    int var_co = 0;

                    //search through temp var list to find which number temp var the token is

                    while (pter2){
                        if(strcmp(tok, pter2->var_name) == 0) {

                            num *pter3 = current_temp_vars;
                            while(pter3->next != NULL){
                                pter3 = pter3->next;
                            } //pter3 is last node of current temp list

                            pter3->next = (num*) malloc(sizeof(num));
                            pter3->next->number = var_co; pter2->next->next = NULL;

                            break;
                        } //place of temp var is in temp number list

                        var_co--;

                        pter2 = pter2->next;
                    }

                    num * pter2_part_two = current_input_list;

                    while(pter2_part_two->next != NULL){
                            pter2_part_two = pter2_part_two->next;
                    }

                    pter2_part_two->number = var_co;

                }

                //Should not reach this point

            }

            tok = strtok(NULL, " ");

        }

        gate * gp = board;

        if(gp->code == 0){
            gp->code = current_gate_code;
            gp->input = current_input_list;
            gp->temp_vars = current_temp_vars;
            gp->output = current_output;
            gp->next = NULL;
        }
        else{

            while(gp->next != NULL){ gp = gp->next; }

            gp->next = (gate*) malloc(sizeof(gate));
            gp->code = current_gate_code;
            gp->input = current_input_list;
            gp->temp_vars = current_temp_vars;
            gp->output = current_output;
            gp->next = NULL;

        }

    } //List of gates initialized

    int vars_length = 0;

    node * ptr_to_find_length_of_vars = vars;

    while(ptr_to_find_length_of_vars){ vars_length++; ptr_to_find_length_of_vars = ptr_to_find_length_of_vars->next; }

    int out_length = 0;

    node * ptr_to_find_length_of_out = out;

    while(ptr_to_find_length_of_out){ out_length++; ptr_to_find_length_of_out = ptr_to_find_length_of_out->next; }

    int temp_length = 0;

    node * ptr_to_find_length_of_temp = temp_vars;

    while(ptr_to_find_length_of_temp){ temp_length++; ptr_to_find_length_of_temp = ptr_to_find_length_of_temp->next; }

    int t = vars_length-1; int exp = 2;

    while(t > 0){ exp = 2*exp; t--; } //exp = 2^(vars_length) which is the possible n-bit binary strings

    int bits[vars_length];

    int arr_out[out_length];
    int arr_temp[temp_length];

    binary(bits, vars_length, 0, 0);

    for(t = 0; t < exp; t++){
        int* cbs = arr_vars[t];

        gate * current_gate = board;

        while(current_gate != NULL){

            if(current_gate->code == 1){
                if(current_gate->input->number >= 0){
                    if(current_gate->output >= 0){
                        arr_out[current_gate->output] = cbs[current_gate->input->number];
                    }
                    else{
                        arr_temp[abs(current_gate->output)] = cbs[current_gate->input->number];
                    }
                }
                else{
                    if(current_gate->output >= 0){
                        arr_out[current_gate->output] = arr_temp[abs(current_gate->input->number)];
                    }
                    else{
                        arr_out[abs(current_gate->output)] = cbs[current_gate->input->number];
                    }
                }
                int d;
                for(d = 0; d < vars_length; d++) printf("%d ", arr_vars[d]);
                printf("| ");
                for(d = 0; d < out_length; d++) printf("%d ", arr_out[d]);
            }
            else if(current_gate->code == 2){

            }
            else if(current_gate->code == 3){

            }
            else if(current_gate->code == 4){

            }
            else if(current_gate->code == 5){

            }
            else if(current_gate->code == 6){

            }
            else if(current_gate->code == 7){

            }

            current_gate = current_gate->next;

        }
    }

    gate * free_mem_board = board;

    while(free_mem_board != NULL){
        num * tmp;
        while(free_mem_board->input != NULL){
            tmp = free_mem_board->input;
            free_mem_board->input = free_mem_board->input->next;
            free(tmp);
        }
        num * tmp2;
        while(free_mem_board->temp_vars != NULL){
            tmp = free_mem_board->temp_vars;
            free_mem_board->temp_vars = free_mem_board->temp_vars->next;
            free(tmp2);
        }
    }

    gate * tmp;

    while(board != NULL){
        tmp = board;
        board = board->next;
        free(tmp);
    }

    node * tmp2;

    while (vars != NULL){
        tmp2 = vars;
        vars = vars->next;
        free(tmp2);
    }

    node * tmp3;

    while (out != NULL){
        tmp3 = out;
        out = out->next;
        free(tmp3);
    }

    node * tmp4;

    while (temp_vars != NULL){
        tmp4 = temp_vars;
        temp_vars = temp_vars->next;
        free(tmp4);
    }

    return 0;
}

void binary(int bits[], int length, int t, int c){

    if (t == length) {
            int f;
            for(f = 0; f < length; f++){
                arr_vars[c][f] = bits[f];
            }
            c++; return;
    }

    bits[t] = 0;
    binary(bits, length, t+1, c);
    bits[t] = 1;
    binary(bits, length, t+1, c);

}

/*

    Memory to free:
         vars list
         out list
         temp_vars list
         input list for every gate
         temp var list for every list
         gate list

*/
