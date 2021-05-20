int isEmpty(Menu *stack){
    if(stack == NULL)
        return 1;
    return 0;
}


void push(Menu **stack, char angka[], char fitur[]){
    Menu *data = (Menu*) malloc(sizeof(Menu));
    strcpy(data->angka, angka);
    strcpy(data->fitur, fitur);
    data->next = NULL;

    if(!isEmpty(*stack)) data->next = *stack;
    *stack = data;
    printf("+%18s%-29s+\n", angka, fitur);
}