import glob
import os
import shutil
import zipfile

import time

from torchsummary import summary
import torch
import torch.nn as nn
from torch.autograd import Variable

from collections import OrderedDict
import numpy as np
from torch.utils.data import Dataset

_test_file_path = "./validation.csv"
# you can use validation.csv to test your model


import pandas as pd
import numpy as np


'''
Here is the final grading script.

Submission file tree should be like this:
- dlmodel.py
- mlmodel.py
- final_model.pth
- training.csv
- report.pdf

Please extremely make sure that the file name is correct. The file name should be exactly the same as the above. The file name is case-sensitive.
We would output the result in the file. If no exception is raised, the code is correct, and the format is acceptable.

If you have any questions, please contact us via email or canvas.
'''

try:
    print("Start grading")
    from mlmodel import MachineLearningModel
    mlmodel = MachineLearningModel()
    df = pd.read_csv(_test_file_path)
    X_test = df.drop('Label', axis=1)
    y_test = df['Label']
    result = mlmodel.predict(X_test)
    print(f'ML Accuracy: {100 * np.mean(result == y_test):.2f} %')
    #######################################

    from dlmodel import *
    def summary(model, input_size, batch_size=-1, device="cuda"):
        def register_hook(module):
            def hook(module, input, output):
                class_name = str(module.__class__).split(".")[-1].split("'")[0]
                module_idx = len(summary)

                m_key = "%s-%i" % (class_name, module_idx + 1)
                summary[m_key] = OrderedDict()
                summary[m_key]["input_shape"] = list(input[0].size())
                summary[m_key]["input_shape"][0] = batch_size
                if isinstance(output, (list, tuple)):
                    summary[m_key]["output_shape"] = [
                        [-1] + list(o.size())[1:] for o in output
                    ]
                else:
                    summary[m_key]["output_shape"] = list(output.size())
                    summary[m_key]["output_shape"][0] = batch_size

                params = 0
                if hasattr(module, "weight") and hasattr(module.weight, "size"):
                    params += torch.prod(torch.LongTensor(list(module.weight.size())))
                    summary[m_key]["trainable"] = module.weight.requires_grad
                if hasattr(module, "bias") and hasattr(module.bias, "size"):
                    params += torch.prod(torch.LongTensor(list(module.bias.size())))
                summary[m_key]["nb_params"] = params

            if (
                not isinstance(module, nn.Sequential)
                and not isinstance(module, nn.ModuleList)
                and not (module == model)
            ):
                hooks.append(module.register_forward_hook(hook))

        device = device.lower()
        assert device in [
            "cuda",
            "cpu",
        ], "Input device is not valid, please specify 'cuda' or 'cpu'"

        if device == "cuda" and torch.cuda.is_available():
            dtype = torch.cuda.FloatTensor
        else:
            dtype = torch.FloatTensor

        # multiple inputs to the network
        if isinstance(input_size, tuple):
            input_size = [input_size]

        # batch_size of 2 for batchnorm
        x = [torch.rand(2, *in_size).type(dtype) for in_size in input_size]
        # print(type(x[0]))

        # create properties
        summary = OrderedDict()
        hooks = []

        # register hook
        model.apply(register_hook)

        # make a forward pass
        # print(x.shape)
        model(*x)

        # remove these hooks
        for h in hooks:
            h.remove()

        line_new = "{:>20}  {:>25} {:>15}".format("Layer (type)", "Output Shape", "Param #")
        # print(line_new)
        print("================================================================")
        total_params = 0
        total_output = 0
        trainable_params = 0
        for layer in summary:
            # input_shape, output_shape, trainable, nb_params
            line_new = "{:>20}  {:>25} {:>15}".format(
                layer,
                str(summary[layer]["output_shape"]),
                "{0:,}".format(summary[layer]["nb_params"]),
            )
            total_params += summary[layer]["nb_params"]
            total_output += np.prod(summary[layer]["output_shape"])
            if "trainable" in summary[layer]:
                if summary[layer]["trainable"] == True:
                    trainable_params += summary[layer]["nb_params"]

        # assume 4 bytes/number (float on cuda).
        total_input_size = abs(np.prod(input_size) * batch_size * 4. / (1024 ** 2.))
        total_output_size = abs(2. * total_output * 4. / (1024 ** 2.))  # x2 for gradients
        total_params_size = abs(total_params.numpy() * 4. / (1024 ** 2.))
        total_size = total_params_size + total_output_size + total_input_size

        print("Total params: {0:,}".format(total_params))
        print("Trainable params: {0:,}".format(trainable_params))
        print("Non-trainable params: {0:,}".format(total_params - trainable_params))
        print("----------------------------------------------------------------")
        print(f'total_params < 100000: {total_params < 100000}')
        return total_params < 100000
        # return summary

    device = 'cpu'

    model = Net()
    lines = (summary(model, (1, 7), device=device))

    print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")

    model = Net()
    model.load_state_dict(torch.load('./final_model.pth'))

    test_set = dataset(file_path = _test_file_path)
    test_loader = torch.utils.data.DataLoader(test_set, batch_size=1, shuffle=False)

    model.eval() # set model to evaluation mode
    with torch.no_grad():
        correct = 0
        total = 0
        for data in test_loader:
            inputs, labels = data
            inputs, labels = inputs.to(device), labels.to(device)
            outputs = model(inputs)
            predicted = torch.round(outputs)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
        print(f"DL Accuracy: {100 * (correct / total):.2f} %")
    print("Finish grading")
except Exception as e:
    print(e)


