/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#define INPUT_IMAGE_SIZE 28*28
#define INPUT_IMAGE_SIDE_SIZE 28

#include "tensorflow/lite/string_type.h"
#include "tensorflow/lite/micro/examples/hello_world/output_handler.h"


void HandleIMGSelectOutput(tflite::ErrorReporter* error_reporter, unsigned char x_value) {
  // Log the current X and Y values
  TF_LITE_REPORT_ERROR(error_reporter, "x_value: %d\nGive new Output:\n", x_value);
}

void HandleMNISTInput(tflite::ErrorReporter* error_reporter, int8_t* output_array) {
  fprintf(stdout, "\n-----New output----\n");
  // Log the current X and Y values
  for (uint32_t i = 0; i < INPUT_IMAGE_SIDE_SIZE; i++) {
    for (uint32_t j = 0; j < INPUT_IMAGE_SIDE_SIZE; j++) {
      // Quantize the input from int to unsigned int
      //uint8_t y = (uint8_t)(
      // Place the quantized input in the model's input tensor
      fprintf(stdout, "%d\t", output_array[i]);
    }
    fprintf(stdout, "\n");
    //error_reporter->Report("\n");
  }
}

void HandleMNISTOutput(tflite::ErrorReporter* error_reporter, int8_t* output_array) {
  fprintf(stdout, "\n-----New output----\n");
  // Log the current X and Y values
  for (uint32_t i = 0; i < 10; i++) {
    // Quantize the input from int to unsigned int
    //uint8_t y = (uint8_t)( + 127) * 2;
    // Place the quantized input in the model's input tensor
    fprintf(stdout, "%d\t", output_array[i]);
  }
}