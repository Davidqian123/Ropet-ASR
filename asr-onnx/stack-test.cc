// asr-onnx/stack-test.cc
//
    

#include "asr-onnx/stack.h"

#include "gtest/gtest.h"
#include "asr-onnx/onnx-utils.h"

namespace sherpa_onnx {

TEST(Stack, Test1DTensors) {
  Ort::AllocatorWithDefaultOptions allocator;

  std::array<int64_t, 1> a_shape{3};
  std::array<int64_t, 1> b_shape{3};

  Ort::Value a = Ort::Value::CreateTensor<float>(allocator, a_shape.data(),
                                                 a_shape.size());

  Ort::Value b = Ort::Value::CreateTensor<float>(allocator, b_shape.data(),
                                                 b_shape.size());
  float *pa = a.GetTensorMutableData<float>();
  float *pb = b.GetTensorMutableData<float>();
  for (int32_t i = 0; i != static_cast<int32_t>(a_shape[0]); ++i) {
    pa[i] = i;
  }
  for (int32_t i = 0; i != static_cast<int32_t>(b_shape[0]); ++i) {
    pb[i] = i + 10;
  }

  Ort::Value ans = Stack(allocator, {&a, &b}, 0);

  Print1D(&a);
  Print1D(&b);
  Print2D(&ans);

  const float *pans = ans.GetTensorData<float>();
  for (int32_t i = 0; i != static_cast<int32_t>(a_shape[0]); ++i) {
    EXPECT_EQ(pa[i], pans[i]);
  }

  for (int32_t i = 0; i != static_cast<int32_t>(b_shape[0]); ++i) {
    EXPECT_EQ(pb[i], pans[i + a_shape[0]]);
  }
}

TEST(Stack, Test2DTensorsDim0) {
  Ort::AllocatorWithDefaultOptions allocator;

  std::array<int64_t, 2> a_shape{2, 3};
  std::array<int64_t, 2> b_shape{2, 3};

  Ort::Value a = Ort::Value::CreateTensor<float>(allocator, a_shape.data(),
                                                 a_shape.size());

  Ort::Value b = Ort::Value::CreateTensor<float>(allocator, b_shape.data(),
                                                 b_shape.size());

  float *pa = a.GetTensorMutableData<float>();
  float *pb = b.GetTensorMutableData<float>();
  for (int32_t i = 0; i != static_cast<int32_t>(a_shape[0] * a_shape[1]); ++i) {
    pa[i] = i;
  }
  for (int32_t i = 0; i != static_cast<int32_t>(b_shape[0] * b_shape[1]); ++i) {
    pb[i] = i + 10;
  }

  Ort::Value ans = Stack(allocator, {&a, &b}, 0);

  Print2D(&a);
  Print2D(&b);
  Print3D(&ans);

  const float *pans = ans.GetTensorData<float>();
  for (int32_t i = 0; i != static_cast<int32_t>(a_shape[0] * a_shape[1]); ++i) {
    EXPECT_EQ(pa[i], pans[i]);
  }
  for (int32_t i = 0; i != static_cast<int32_t>(b_shape[0] * b_shape[1]); ++i) {
    EXPECT_EQ(pb[i], pans[i + a_shape[0] * a_shape[1]]);
  }
}

TEST(Stack, Test2DTensorsDim1) {
  Ort::AllocatorWithDefaultOptions allocator;

  std::array<int64_t, 2> a_shape{4, 3};
  std::array<int64_t, 2> b_shape{4, 3};

  Ort::Value a = Ort::Value::CreateTensor<float>(allocator, a_shape.data(),
                                                 a_shape.size());

  Ort::Value b = Ort::Value::CreateTensor<float>(allocator, b_shape.data(),
                                                 b_shape.size());

  float *pa = a.GetTensorMutableData<float>();
  float *pb = b.GetTensorMutableData<float>();
  for (int32_t i = 0; i != static_cast<int32_t>(a_shape[0] * a_shape[1]); ++i) {
    pa[i] = i;
  }
  for (int32_t i = 0; i != static_cast<int32_t>(b_shape[0] * b_shape[1]); ++i) {
    pb[i] = i + 10;
  }

  Ort::Value ans = Stack(allocator, {&a, &b}, 1);

  Print2D(&a);
  Print2D(&b);
  Print3D(&ans);

  const float *pans = ans.GetTensorData<float>();

  for (int32_t r = 0; r != static_cast<int32_t>(a_shape[0]); ++r) {
    for (int32_t i = 0; i != static_cast<int32_t>(a_shape[1]);
         ++i, ++pa, ++pans) {
      EXPECT_EQ(*pa, *pans);
    }

    for (int32_t i = 0; i != static_cast<int32_t>(b_shape[1]);
         ++i, ++pb, ++pans) {
      EXPECT_EQ(*pb, *pans);
    }
  }
}

TEST(Stack, Test3DTensorsDim0) {
  Ort::AllocatorWithDefaultOptions allocator;

  std::array<int64_t, 3> a_shape{2, 3, 2};
  std::array<int64_t, 3> b_shape{2, 3, 2};

  Ort::Value a = Ort::Value::CreateTensor<float>(allocator, a_shape.data(),
                                                 a_shape.size());

  Ort::Value b = Ort::Value::CreateTensor<float>(allocator, b_shape.data(),
                                                 b_shape.size());

  float *pa = a.GetTensorMutableData<float>();
  float *pb = b.GetTensorMutableData<float>();
  for (int32_t i = 0;
       i != static_cast<int32_t>(a_shape[0] * a_shape[1] * a_shape[2]); ++i) {
    pa[i] = i;
  }
  for (int32_t i = 0;
       i != static_cast<int32_t>(b_shape[0] * b_shape[1] * b_shape[2]); ++i) {
    pb[i] = i + 10;
  }

  Ort::Value ans = Stack(allocator, {&a, &b}, 0);

  const float *pans = ans.GetTensorData<float>();
  for (int32_t i = 0;
       i != static_cast<int32_t>(a_shape[0] * a_shape[1] * a_shape[2]); ++i) {
    EXPECT_EQ(pa[i], pans[i]);
  }
  for (int32_t i = 0;
       i != static_cast<int32_t>(b_shape[0] * b_shape[1] * b_shape[2]); ++i) {
    EXPECT_EQ(pb[i], pans[i + a_shape[0] * a_shape[1] * a_shape[2]]);
  }

  Print3D(&a);
  Print3D(&b);
  Print4D(&ans);
}

TEST(Stack, Test3DTensorsDim1) {
  Ort::AllocatorWithDefaultOptions allocator;

  std::array<int64_t, 3> a_shape{2, 2, 3};
  std::array<int64_t, 3> b_shape{2, 2, 3};

  Ort::Value a = Ort::Value::CreateTensor<float>(allocator, a_shape.data(),
                                                 a_shape.size());

  Ort::Value b = Ort::Value::CreateTensor<float>(allocator, b_shape.data(),
                                                 b_shape.size());

  float *pa = a.GetTensorMutableData<float>();
  float *pb = b.GetTensorMutableData<float>();
  for (int32_t i = 0;
       i != static_cast<int32_t>(a_shape[0] * a_shape[1] * a_shape[2]); ++i) {
    pa[i] = i;
  }
  for (int32_t i = 0;
       i != static_cast<int32_t>(b_shape[0] * b_shape[1] * b_shape[2]); ++i) {
    pb[i] = i + 10;
  }

  Ort::Value ans = Stack(allocator, {&a, &b}, 1);

  const float *pans = ans.GetTensorData<float>();

  for (int32_t i = 0; i != static_cast<int32_t>(a_shape[0]); ++i) {
    for (int32_t k = 0; k != static_cast<int32_t>(a_shape[1] * a_shape[2]);
         ++k, ++pa, ++pans) {
      EXPECT_EQ(*pa, *pans);
    }

    for (int32_t k = 0; k != static_cast<int32_t>(b_shape[1] * b_shape[2]);
         ++k, ++pb, ++pans) {
      EXPECT_EQ(*pb, *pans);
    }
  }

  Print3D(&a);
  Print3D(&b);
  Print4D(&ans);
}

TEST(Stack, Test3DTensorsDim2) {
  Ort::AllocatorWithDefaultOptions allocator;

  std::array<int64_t, 3> a_shape{2, 3, 4};
  std::array<int64_t, 3> b_shape{2, 3, 4};

  Ort::Value a = Ort::Value::CreateTensor<float>(allocator, a_shape.data(),
                                                 a_shape.size());

  Ort::Value b = Ort::Value::CreateTensor<float>(allocator, b_shape.data(),
                                                 b_shape.size());

  float *pa = a.GetTensorMutableData<float>();
  float *pb = b.GetTensorMutableData<float>();
  for (int32_t i = 0;
       i != static_cast<int32_t>(a_shape[0] * a_shape[1] * a_shape[2]); ++i) {
    pa[i] = i;
  }
  for (int32_t i = 0;
       i != static_cast<int32_t>(b_shape[0] * b_shape[1] * b_shape[2]); ++i) {
    pb[i] = i + 10;
  }

  Ort::Value ans = Stack(allocator, {&a, &b}, 2);

  const float *pans = ans.GetTensorData<float>();

  for (int32_t i = 0; i != static_cast<int32_t>(a_shape[0] * a_shape[1]); ++i) {
    for (int32_t k = 0; k != static_cast<int32_t>(a_shape[2]);
         ++k, ++pa, ++pans) {
      EXPECT_EQ(*pa, *pans);
    }

    for (int32_t k = 0; k != static_cast<int32_t>(b_shape[2]);
         ++k, ++pb, ++pans) {
      EXPECT_EQ(*pb, *pans);
    }
  }

  Print3D(&a);
  Print3D(&b);
  Print4D(&ans);
}

}  // namespace sherpa_onnx
