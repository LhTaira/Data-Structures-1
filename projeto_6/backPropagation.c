double activationDerivative(int x) {
    return exp(-x)/pow((1 + exp(-x)), 2);
}

double weightValueSum(List* layer, double *layerDelta, int neuronConnection) {
    double sum = 0;
    int *weight;

    for(int c = 0; c < getListSize(layer); c++) {
        weight = getList(layer, c)->element.w;
        sum += layerDelta[c] * weight[neuronConnection];
    }

    return 0;
}

void propagate(short int expectedValue, double *output, List *outputNeuronLayer, List *hiddenNeuronLayer, List *inputNeuronLayer, int argc, double *hiddenLayerOutput, double *inputLayerOutput) {
			double outputDelta = activationDerivative(*output) * (expectedValue - *output);
			getList(outputNeuronLayer, 0)->element.b += 2 * 0.1 * (*output) * outputDelta;
			double *hiddenLayerDelta = (double *) malloc(sizeof(double) * argc);

			//Peso atualiza depois

			//Hidden Layer
			for(int neuronCounter = 0; neuronCounter < argc; neuronCounter++) {
				double valueDerivative = activationDerivative(*(hiddenLayerOutput + neuronCounter));
				double delta = valueDerivative * (outputDelta * outputNeuronLayer->element.w[0]);
				*(hiddenLayerDelta + neuronCounter) = delta;

				getList(hiddenNeuronLayer, neuronCounter)->element.b = getList(hiddenNeuronLayer, neuronCounter)->element.b + (2 * 0.1 * (*(hiddenLayerOutput + neuronCounter)) * delta);
			}

			//Input Layer
			for(int neuronCounter = 0; neuronCounter < 536; neuronCounter++) {
				double valueDerivative = activationDerivative(*(inputLayerOutput + neuronCounter));
				double delta = valueDerivative * weightValueSum(hiddenNeuronLayer, hiddenLayerDelta, neuronCounter);

				getList(inputNeuronLayer, neuronCounter)->element.b = getList(inputNeuronLayer, neuronCounter)->element.b + (2 * 0.1 * (*(inputLayerOutput + neuronCounter)) * delta);
				for(int k = 0; k < 536; k++)
					getList(inputNeuronLayer, neuronCounter)->element.w[k] = getList(inputNeuronLayer, neuronCounter)->element.w[k] + (2 * 0.1 * (*(inputLayerOutput + neuronCounter)) * delta);
			}

			//Hidden layer weight
			for(int neuronCounter = 0; neuronCounter < argc; neuronCounter++) {
				double valueDerivative = activationDerivative(*(hiddenLayerOutput + neuronCounter));
				double delta = valueDerivative * (outputDelta * outputNeuronLayer->element.w[0]);
				*(hiddenLayerDelta + neuronCounter) = delta;
				for(int k = 0; k < 536; k++)
					getList(hiddenNeuronLayer, neuronCounter)->element.w[k] = getList(hiddenNeuronLayer, neuronCounter)->element.w[k] + (2 * 0.1 * (*(hiddenLayerOutput + neuronCounter)) * delta);
			}

			for(int c = 0; c < argc; c++)
				getList(outputNeuronLayer, 0)->element.w[c] += 2 * 0.1 * (*output) * outputDelta;

            free(hiddenLayerDelta);
}