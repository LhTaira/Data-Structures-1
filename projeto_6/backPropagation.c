double activationDerivative(int x) {
    return exp(-x)/pow((1 + exp(-x)), 2);
}

double weightValueSum(List* layer, double *layerDelta, int neuronConnection) {
    double sum = 0;
    double weight;

    for(int c = 0; c < getListSize(layer); c++) {
        weight = getList(layer, c)->w;
        sum += layerDelta[c] * weight[neuronConnection];
    }

    return 0;
}