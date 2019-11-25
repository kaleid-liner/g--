int i1 = 0;
int i2;
float f1 = 1;
float f2;
int array[3];
int array2[4] = {1};

void main() {
    int a = i1;
    float b;
    float c = 1;
    float d[3] = {1, 2, 3};
    float k[4] = {a, b, c, d[2]};
    output_fvar = k[3];
    outputFloat();
    output_ivar = array[0];
    outputInt();
    output_ivar = array2[2];
    outputInt();
}
