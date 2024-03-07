// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: edy.proto

#ifndef PROTOBUF_edy_2eproto__INCLUDED
#define PROTOBUF_edy_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_edy_2eproto();
void protobuf_AssignDesc_edy_2eproto();
void protobuf_ShutdownFile_edy_2eproto();

class EmbeddedMessage;
class EdyMsg;

// ===================================================================

class EmbeddedMessage : public ::google::protobuf::Message {
 public:
  EmbeddedMessage();
  virtual ~EmbeddedMessage();

  EmbeddedMessage(const EmbeddedMessage& from);

  inline EmbeddedMessage& operator=(const EmbeddedMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const EmbeddedMessage& default_instance();

  void Swap(EmbeddedMessage* other);

  // implements Message ----------------------------------------------

  EmbeddedMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EmbeddedMessage& from);
  void MergeFrom(const EmbeddedMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 mSubCmd = 1;
  inline bool has_msubcmd() const;
  inline void clear_msubcmd();
  static const int kMSubCmdFieldNumber = 1;
  inline ::google::protobuf::uint32 msubcmd() const;
  inline void set_msubcmd(::google::protobuf::uint32 value);

  // required string strParams = 2;
  inline bool has_strparams() const;
  inline void clear_strparams();
  static const int kStrParamsFieldNumber = 2;
  inline const ::std::string& strparams() const;
  inline void set_strparams(const ::std::string& value);
  inline void set_strparams(const char* value);
  inline void set_strparams(const char* value, size_t size);
  inline ::std::string* mutable_strparams();
  inline ::std::string* release_strparams();
  inline void set_allocated_strparams(::std::string* strparams);

  // @@protoc_insertion_point(class_scope:EmbeddedMessage)
 private:
  inline void set_has_msubcmd();
  inline void clear_has_msubcmd();
  inline void set_has_strparams();
  inline void clear_has_strparams();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* strparams_;
  ::google::protobuf::uint32 msubcmd_;
  friend void  protobuf_AddDesc_edy_2eproto();
  friend void protobuf_AssignDesc_edy_2eproto();
  friend void protobuf_ShutdownFile_edy_2eproto();

  void InitAsDefaultInstance();
  static EmbeddedMessage* default_instance_;
};
// -------------------------------------------------------------------

class EdyMsg : public ::google::protobuf::Message {
 public:
  EdyMsg();
  virtual ~EdyMsg();

  EdyMsg(const EdyMsg& from);

  inline EdyMsg& operator=(const EdyMsg& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const EdyMsg& default_instance();

  void Swap(EdyMsg* other);

  // implements Message ----------------------------------------------

  EdyMsg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EdyMsg& from);
  void MergeFrom(const EdyMsg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 nCmd = 1 [default = 0];
  inline bool has_ncmd() const;
  inline void clear_ncmd();
  static const int kNCmdFieldNumber = 1;
  inline ::google::protobuf::uint32 ncmd() const;
  inline void set_ncmd(::google::protobuf::uint32 value);

  // required string strData = 2;
  inline bool has_strdata() const;
  inline void clear_strdata();
  static const int kStrDataFieldNumber = 2;
  inline const ::std::string& strdata() const;
  inline void set_strdata(const ::std::string& value);
  inline void set_strdata(const char* value);
  inline void set_strdata(const char* value, size_t size);
  inline ::std::string* mutable_strdata();
  inline ::std::string* release_strdata();
  inline void set_allocated_strdata(::std::string* strdata);

  // optional .EmbeddedMessage subMsg = 3;
  inline bool has_submsg() const;
  inline void clear_submsg();
  static const int kSubMsgFieldNumber = 3;
  inline const ::EmbeddedMessage& submsg() const;
  inline ::EmbeddedMessage* mutable_submsg();
  inline ::EmbeddedMessage* release_submsg();
  inline void set_allocated_submsg(::EmbeddedMessage* submsg);

  // @@protoc_insertion_point(class_scope:EdyMsg)
 private:
  inline void set_has_ncmd();
  inline void clear_has_ncmd();
  inline void set_has_strdata();
  inline void clear_has_strdata();
  inline void set_has_submsg();
  inline void clear_has_submsg();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* strdata_;
  ::EmbeddedMessage* submsg_;
  ::google::protobuf::uint32 ncmd_;
  friend void  protobuf_AddDesc_edy_2eproto();
  friend void protobuf_AssignDesc_edy_2eproto();
  friend void protobuf_ShutdownFile_edy_2eproto();

  void InitAsDefaultInstance();
  static EdyMsg* default_instance_;
};
// ===================================================================


// ===================================================================

// EmbeddedMessage

// required uint32 mSubCmd = 1;
inline bool EmbeddedMessage::has_msubcmd() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EmbeddedMessage::set_has_msubcmd() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EmbeddedMessage::clear_has_msubcmd() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EmbeddedMessage::clear_msubcmd() {
  msubcmd_ = 0u;
  clear_has_msubcmd();
}
inline ::google::protobuf::uint32 EmbeddedMessage::msubcmd() const {
  // @@protoc_insertion_point(field_get:EmbeddedMessage.mSubCmd)
  return msubcmd_;
}
inline void EmbeddedMessage::set_msubcmd(::google::protobuf::uint32 value) {
  set_has_msubcmd();
  msubcmd_ = value;
  // @@protoc_insertion_point(field_set:EmbeddedMessage.mSubCmd)
}

// required string strParams = 2;
inline bool EmbeddedMessage::has_strparams() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void EmbeddedMessage::set_has_strparams() {
  _has_bits_[0] |= 0x00000002u;
}
inline void EmbeddedMessage::clear_has_strparams() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void EmbeddedMessage::clear_strparams() {
  if (strparams_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strparams_->clear();
  }
  clear_has_strparams();
}
inline const ::std::string& EmbeddedMessage::strparams() const {
  // @@protoc_insertion_point(field_get:EmbeddedMessage.strParams)
  return *strparams_;
}
inline void EmbeddedMessage::set_strparams(const ::std::string& value) {
  set_has_strparams();
  if (strparams_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strparams_ = new ::std::string;
  }
  strparams_->assign(value);
  // @@protoc_insertion_point(field_set:EmbeddedMessage.strParams)
}
inline void EmbeddedMessage::set_strparams(const char* value) {
  set_has_strparams();
  if (strparams_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strparams_ = new ::std::string;
  }
  strparams_->assign(value);
  // @@protoc_insertion_point(field_set_char:EmbeddedMessage.strParams)
}
inline void EmbeddedMessage::set_strparams(const char* value, size_t size) {
  set_has_strparams();
  if (strparams_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strparams_ = new ::std::string;
  }
  strparams_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:EmbeddedMessage.strParams)
}
inline ::std::string* EmbeddedMessage::mutable_strparams() {
  set_has_strparams();
  if (strparams_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strparams_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:EmbeddedMessage.strParams)
  return strparams_;
}
inline ::std::string* EmbeddedMessage::release_strparams() {
  clear_has_strparams();
  if (strparams_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = strparams_;
    strparams_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void EmbeddedMessage::set_allocated_strparams(::std::string* strparams) {
  if (strparams_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete strparams_;
  }
  if (strparams) {
    set_has_strparams();
    strparams_ = strparams;
  } else {
    clear_has_strparams();
    strparams_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:EmbeddedMessage.strParams)
}

// -------------------------------------------------------------------

// EdyMsg

// required uint32 nCmd = 1 [default = 0];
inline bool EdyMsg::has_ncmd() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EdyMsg::set_has_ncmd() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EdyMsg::clear_has_ncmd() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EdyMsg::clear_ncmd() {
  ncmd_ = 0u;
  clear_has_ncmd();
}
inline ::google::protobuf::uint32 EdyMsg::ncmd() const {
  // @@protoc_insertion_point(field_get:EdyMsg.nCmd)
  return ncmd_;
}
inline void EdyMsg::set_ncmd(::google::protobuf::uint32 value) {
  set_has_ncmd();
  ncmd_ = value;
  // @@protoc_insertion_point(field_set:EdyMsg.nCmd)
}

// required string strData = 2;
inline bool EdyMsg::has_strdata() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void EdyMsg::set_has_strdata() {
  _has_bits_[0] |= 0x00000002u;
}
inline void EdyMsg::clear_has_strdata() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void EdyMsg::clear_strdata() {
  if (strdata_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strdata_->clear();
  }
  clear_has_strdata();
}
inline const ::std::string& EdyMsg::strdata() const {
  // @@protoc_insertion_point(field_get:EdyMsg.strData)
  return *strdata_;
}
inline void EdyMsg::set_strdata(const ::std::string& value) {
  set_has_strdata();
  if (strdata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strdata_ = new ::std::string;
  }
  strdata_->assign(value);
  // @@protoc_insertion_point(field_set:EdyMsg.strData)
}
inline void EdyMsg::set_strdata(const char* value) {
  set_has_strdata();
  if (strdata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strdata_ = new ::std::string;
  }
  strdata_->assign(value);
  // @@protoc_insertion_point(field_set_char:EdyMsg.strData)
}
inline void EdyMsg::set_strdata(const char* value, size_t size) {
  set_has_strdata();
  if (strdata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strdata_ = new ::std::string;
  }
  strdata_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:EdyMsg.strData)
}
inline ::std::string* EdyMsg::mutable_strdata() {
  set_has_strdata();
  if (strdata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    strdata_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:EdyMsg.strData)
  return strdata_;
}
inline ::std::string* EdyMsg::release_strdata() {
  clear_has_strdata();
  if (strdata_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = strdata_;
    strdata_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void EdyMsg::set_allocated_strdata(::std::string* strdata) {
  if (strdata_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete strdata_;
  }
  if (strdata) {
    set_has_strdata();
    strdata_ = strdata;
  } else {
    clear_has_strdata();
    strdata_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:EdyMsg.strData)
}

// optional .EmbeddedMessage subMsg = 3;
inline bool EdyMsg::has_submsg() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void EdyMsg::set_has_submsg() {
  _has_bits_[0] |= 0x00000004u;
}
inline void EdyMsg::clear_has_submsg() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void EdyMsg::clear_submsg() {
  if (submsg_ != NULL) submsg_->::EmbeddedMessage::Clear();
  clear_has_submsg();
}
inline const ::EmbeddedMessage& EdyMsg::submsg() const {
  // @@protoc_insertion_point(field_get:EdyMsg.subMsg)
  return submsg_ != NULL ? *submsg_ : *default_instance_->submsg_;
}
inline ::EmbeddedMessage* EdyMsg::mutable_submsg() {
  set_has_submsg();
  if (submsg_ == NULL) submsg_ = new ::EmbeddedMessage;
  // @@protoc_insertion_point(field_mutable:EdyMsg.subMsg)
  return submsg_;
}
inline ::EmbeddedMessage* EdyMsg::release_submsg() {
  clear_has_submsg();
  ::EmbeddedMessage* temp = submsg_;
  submsg_ = NULL;
  return temp;
}
inline void EdyMsg::set_allocated_submsg(::EmbeddedMessage* submsg) {
  delete submsg_;
  submsg_ = submsg;
  if (submsg) {
    set_has_submsg();
  } else {
    clear_has_submsg();
  }
  // @@protoc_insertion_point(field_set_allocated:EdyMsg.subMsg)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_edy_2eproto__INCLUDED