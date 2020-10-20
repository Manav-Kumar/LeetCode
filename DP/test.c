struct Duplet
{
    int index,size;
    int* ptr;
};

int compare(const void*p, const void* q)
{

    return (*(int *)p - *(int*)q);
}

int comparater(const void *p, const void *q)
{
    int size = ((struct Duplet *)p)->size;
    int *l = ((struct Duplet *)p)->ptr;
    int *r = ((struct Duplet *)q)->ptr;
    for(int i=size-1;i>=0;i--)
    {
        if(l[i] != r[i])
        {
            return l[i] - r[i];
        }
    }
    return 0;
}

int* sortBinaryNumbers(int bitArrays_rows, int bitArrays_columns, int** bitArrays, int* result_count) {
    struct Duplet *arr = (struct Duplet *) malloc(bitArrays_rows * (sizeof(struct Duplet)));

    for(int i=0;i<bitArrays_rows;i++)
    {
        qsort((void*)(bitArrays[i]), bitArrays_columns, sizeof(int), compare);
        arr[i].index = i;
        arr[i].ptr = bitArrays[i];
        arr[i].size = bitArrays_columns;
    }
    qsort((void *)(arr), bitArrays_rows, sizeof(struct Duplet), comparater);
    int *sol = (int *) malloc(bitArrays_rows * sizeof(int));
    for(int i=0;i<bitArrays_rows;i++)
    {
        sol[i] = arr[i].index;
    }
    return sol;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int bitArrays_rows = parse_int(ltrim(rtrim(readline())));

    int bitArrays_columns = parse_int(ltrim(rtrim(readline())));

    int** bitArrays = malloc(bitArrays_rows * sizeof(int*));

    for (int i = 0; i < bitArrays_rows; i++) {
        *(bitArrays + i) = malloc(bitArrays_columns * (sizeof(int)));

        char** bitArrays_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < bitArrays_columns; j++) {
            int bitArrays_item = parse_int(*(bitArrays_item_temp + j));

            *(*(bitArrays + i) + j) = bitArrays_item;
        }
    }

    int result_count;
    int* result = sortBinaryNumbers(bitArrays_rows, bitArrays_columns, bitArrays, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}