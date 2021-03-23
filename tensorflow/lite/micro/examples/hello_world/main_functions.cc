/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

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

#include "tensorflow/lite/micro/examples/hello_world/main_functions.h"

#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/examples/hello_world/constants.h"
#include "tensorflow/lite/micro/examples/hello_world/model.h"
#include "tensorflow/lite/micro/examples/hello_world/output_handler.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
<<<<<<< HEAD
#include "tensorflow/lite/micro/recording_micro_interpreter.h"
=======
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
>>>>>>> 682f7806e367f93db724118e62d72f282bc5cb91
#include "tensorflow/lite/schema/schema_generated.h"

#include "tensorflow/lite/micro/examples/hello_world/input_images.h"

#define INPUT_IMAGE_SIZE 28*28
#define INPUT_IMAGE_SIDE_SIZE 28

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::RecordingMicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

constexpr int kTensorArenaSize = 16 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

unsigned char img_select = 0;
const unsigned char* imgs;
int8_t* output_array;
}  // namespace

// The name of this function is important for Arduino compatibility.
void setup() {
  tflite::InitializeTarget();

  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  TF_LITE_REPORT_ERROR(error_reporter, "Loading model\n");
  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::AllOpsResolver resolver;

  TF_LITE_REPORT_ERROR(error_reporter, "Initiating interpreter\n");
  // Build an interpreter to run the model with.
  static tflite::RecordingMicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  TF_LITE_REPORT_ERROR(error_reporter, "Allocating memory\n");
  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);


  imgs = s_imgs;

  // Keep track of how many inferences we have performed.
  interpreter->GetMicroAllocator().PrintAllocations();
}

// The name of this function is important for Arduino compatibility.
void loop() {
  // Calculate an x value to feed into the model. We compare the current
  // inference_count to the number of inferences per cycle to determine
  // our position within the range of possible x values the model was
  // trained on, and use this to calculate a value.
  
  //float x = position * kXrange;
  /*
  char s[256];
  if(fgets(s, 4, stdin)) {}
  
    //TF_LITE_REPORT_ERROR(error_reporter, "Received %f:\n", static_cast<double>(position));
    
    for (uint32_t i = 0; i < INPUT_IMAGE_SIZE; i++) { 
      if (i%28 == 0) {
        fprintf(stdout, "\n");
      }
      // Quantize the input from floating-point to integer
      input->data.int8[i] = (int8_t)(imgs[img_select*INPUT_IMAGE_SIZE + i]/2) - 127;
      // Place the quantized input in the model's input tensor
      fprintf(stdout, "%d\t", input->data.int8[i]);
    }
    */

  //if(fgets(s, 4, stdin)) {}
    // Run inference, and report any error
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
      TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed\n");
      return;
    }

    // Obtain the quantized output from model's output tensor
    //int8_t y_quantized = output->data.int8[0];
    // Dequantize the output from integer to floating-point
    //float y = (y_quantized - output->params.zero_point) * output->params.scale;

    // Output the results. A custom HandleOutput function can be implemented
    // for each supported hardware target.
    //HandleOutput(error_reporter, x, y);

  //}

  output_array = output->data.int8;
  //HandleMNISTOutput(error_reporter, output_array);
  //HandleIMGSelectOutput(error_reporter, img_select);
  
  // Increment the inference_counter, and reset it if we have reached
  // the total number per cycle
  img_select = (img_select + 1) % 2;
}
