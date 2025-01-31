/*!
 *  Copyright (c) 2023 by Contributors
 * \file serve/data.h
 */
#ifndef MLC_LLM_SERVE_DATA_H_
#define MLC_LLM_SERVE_DATA_H_

#include <tvm/runtime/container/shape_tuple.h>
#include <tvm/runtime/container/string.h>
#include <tvm/runtime/ndarray.h>
#include <tvm/runtime/object.h>

namespace mlc {
namespace llm {
namespace serve {

using namespace tvm::runtime;

class Model;

/****************** DataNode ******************/

/*! \brief The base class of multi-modality data (text, tokens, embedding, etc). */
class DataNode : public Object {
 public:
  /*! \brief Get the length (equivalent number of tokens) of the data. */
  virtual int GetLength() const = 0;

  /*! \brief Compute the embedding of this data with regard to the input model. */
  virtual NDArray GetEmbedding(Model model) const = 0;

  static constexpr const char* _type_key = "mlc.serve.Data";
  static constexpr const bool _type_has_method_sequal_reduce = false;
  static constexpr const bool _type_has_method_shash_reduce = false;
  TVM_DECLARE_BASE_OBJECT_INFO(DataNode, Object);
};

class Data : public ObjectRef {
 public:
  TVM_DEFINE_OBJECT_REF_METHODS(Data, ObjectRef, DataNode);
};

/****************** TextDataNode ******************/

/*! \brief The class of text data, containing a text string. */
class TextDataNode : public DataNode {
 public:
  /*! \brief The text string. */
  String text;

  int GetLength() const final;
  NDArray GetEmbedding(Model model) const final;

  static constexpr const char* _type_key = "mlc.serve.TextData";
  TVM_DECLARE_BASE_OBJECT_INFO(TextDataNode, DataNode);
};

class TextData : public Data {
 public:
  explicit TextData(String text);

  TVM_DEFINE_OBJECT_REF_METHODS(TextData, Data, TextDataNode);
};

/****************** TokenDataNode ******************/

/*! \brief The class of token data, containing a list of token ids. */
class TokenDataNode : public DataNode {
 public:
  /*! \brief The token ids. */
  IntTuple token_ids;

  int GetLength() const final;
  NDArray GetEmbedding(Model model) const final;

  static constexpr const char* _type_key = "mlc.serve.TokenData";
  TVM_DECLARE_BASE_OBJECT_INFO(TokenDataNode, DataNode);
};

class TokenData : public Data {
 public:
  explicit TokenData(IntTuple token_ids);

  explicit TokenData(std::vector<int32_t> token_ids);

  TVM_DEFINE_OBJECT_REF_METHODS(TokenData, Data, TokenDataNode);
};

}  // namespace serve
}  // namespace llm
}  // namespace mlc

#endif  // MLC_LLM_SERVE_DATA_H_
