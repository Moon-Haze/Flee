// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DevInfo.proto
// Protobuf C++ Version: 4.25.0

#ifndef GOOGLE_PROTOBUF_INCLUDED_DevInfo_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_DevInfo_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4025000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4025000 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_DevInfo_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_DevInfo_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_DevInfo_2eproto;
namespace Flee {
class DevInfo;
struct DevInfoDefaultTypeInternal;
extern DevInfoDefaultTypeInternal _DevInfo_default_instance_;
}  // namespace Flee
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace Flee {

// ===================================================================


// -------------------------------------------------------------------

class DevInfo final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Flee.DevInfo) */ {
 public:
  inline DevInfo() : DevInfo(nullptr) {}
  ~DevInfo() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR DevInfo(::google::protobuf::internal::ConstantInitialized);

  inline DevInfo(const DevInfo& from)
      : DevInfo(nullptr, from) {}
  DevInfo(DevInfo&& from) noexcept
    : DevInfo() {
    *this = ::std::move(from);
  }

  inline DevInfo& operator=(const DevInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline DevInfo& operator=(DevInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const DevInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const DevInfo* internal_default_instance() {
    return reinterpret_cast<const DevInfo*>(
               &_DevInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(DevInfo& a, DevInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(DevInfo* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr &&
        GetArena() == other->GetArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(DevInfo* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  DevInfo* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<DevInfo>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const DevInfo& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const DevInfo& from) {
    DevInfo::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  ::google::protobuf::internal::CachedSize* AccessCachedSize() const final;
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(DevInfo* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "Flee.DevInfo";
  }
  protected:
  explicit DevInfo(::google::protobuf::Arena* arena);
  DevInfo(::google::protobuf::Arena* arena, const DevInfo& from);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBootloaderFieldNumber = 1,
    kProcVersionFieldNumber = 2,
    kCodenameFieldNumber = 3,
    kIncrementalFieldNumber = 4,
    kFingerprintFieldNumber = 5,
    kBootIdFieldNumber = 6,
    kAndroidIdFieldNumber = 7,
    kBaseBandFieldNumber = 8,
    kInnerVersionFieldNumber = 9,
  };
  // optional bytes bootloader = 1;
  bool has_bootloader() const;
  void clear_bootloader() ;
  const std::string& bootloader() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_bootloader(Arg_&& arg, Args_... args);
  std::string* mutable_bootloader();
  PROTOBUF_NODISCARD std::string* release_bootloader();
  void set_allocated_bootloader(std::string* value);

  private:
  const std::string& _internal_bootloader() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_bootloader(
      const std::string& value);
  std::string* _internal_mutable_bootloader();

  public:
  // optional bytes procVersion = 2;
  bool has_procversion() const;
  void clear_procversion() ;
  const std::string& procversion() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_procversion(Arg_&& arg, Args_... args);
  std::string* mutable_procversion();
  PROTOBUF_NODISCARD std::string* release_procversion();
  void set_allocated_procversion(std::string* value);

  private:
  const std::string& _internal_procversion() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_procversion(
      const std::string& value);
  std::string* _internal_mutable_procversion();

  public:
  // optional bytes codename = 3;
  bool has_codename() const;
  void clear_codename() ;
  const std::string& codename() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_codename(Arg_&& arg, Args_... args);
  std::string* mutable_codename();
  PROTOBUF_NODISCARD std::string* release_codename();
  void set_allocated_codename(std::string* value);

  private:
  const std::string& _internal_codename() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_codename(
      const std::string& value);
  std::string* _internal_mutable_codename();

  public:
  // optional bytes incremental = 4;
  bool has_incremental() const;
  void clear_incremental() ;
  const std::string& incremental() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_incremental(Arg_&& arg, Args_... args);
  std::string* mutable_incremental();
  PROTOBUF_NODISCARD std::string* release_incremental();
  void set_allocated_incremental(std::string* value);

  private:
  const std::string& _internal_incremental() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_incremental(
      const std::string& value);
  std::string* _internal_mutable_incremental();

  public:
  // optional bytes fingerprint = 5;
  bool has_fingerprint() const;
  void clear_fingerprint() ;
  const std::string& fingerprint() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_fingerprint(Arg_&& arg, Args_... args);
  std::string* mutable_fingerprint();
  PROTOBUF_NODISCARD std::string* release_fingerprint();
  void set_allocated_fingerprint(std::string* value);

  private:
  const std::string& _internal_fingerprint() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_fingerprint(
      const std::string& value);
  std::string* _internal_mutable_fingerprint();

  public:
  // optional bytes bootId = 6;
  bool has_bootid() const;
  void clear_bootid() ;
  const std::string& bootid() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_bootid(Arg_&& arg, Args_... args);
  std::string* mutable_bootid();
  PROTOBUF_NODISCARD std::string* release_bootid();
  void set_allocated_bootid(std::string* value);

  private:
  const std::string& _internal_bootid() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_bootid(
      const std::string& value);
  std::string* _internal_mutable_bootid();

  public:
  // optional bytes androidId = 7;
  bool has_androidid() const;
  void clear_androidid() ;
  const std::string& androidid() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_androidid(Arg_&& arg, Args_... args);
  std::string* mutable_androidid();
  PROTOBUF_NODISCARD std::string* release_androidid();
  void set_allocated_androidid(std::string* value);

  private:
  const std::string& _internal_androidid() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_androidid(
      const std::string& value);
  std::string* _internal_mutable_androidid();

  public:
  // optional bytes baseBand = 8;
  bool has_baseband() const;
  void clear_baseband() ;
  const std::string& baseband() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_baseband(Arg_&& arg, Args_... args);
  std::string* mutable_baseband();
  PROTOBUF_NODISCARD std::string* release_baseband();
  void set_allocated_baseband(std::string* value);

  private:
  const std::string& _internal_baseband() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_baseband(
      const std::string& value);
  std::string* _internal_mutable_baseband();

  public:
  // optional bytes innerVersion = 9;
  bool has_innerversion() const;
  void clear_innerversion() ;
  const std::string& innerversion() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_innerversion(Arg_&& arg, Args_... args);
  std::string* mutable_innerversion();
  PROTOBUF_NODISCARD std::string* release_innerversion();
  void set_allocated_innerversion(std::string* value);

  private:
  const std::string& _internal_innerversion() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_innerversion(
      const std::string& value);
  std::string* _internal_mutable_innerversion();

  public:
  // @@protoc_insertion_point(class_scope:Flee.DevInfo)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      4, 9, 0,
      0, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {

        inline explicit constexpr Impl_(
            ::google::protobuf::internal::ConstantInitialized) noexcept;
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena);
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::google::protobuf::internal::ArenaStringPtr bootloader_;
    ::google::protobuf::internal::ArenaStringPtr procversion_;
    ::google::protobuf::internal::ArenaStringPtr codename_;
    ::google::protobuf::internal::ArenaStringPtr incremental_;
    ::google::protobuf::internal::ArenaStringPtr fingerprint_;
    ::google::protobuf::internal::ArenaStringPtr bootid_;
    ::google::protobuf::internal::ArenaStringPtr androidid_;
    ::google::protobuf::internal::ArenaStringPtr baseband_;
    ::google::protobuf::internal::ArenaStringPtr innerversion_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_DevInfo_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// DevInfo

// optional bytes bootloader = 1;
inline bool DevInfo::has_bootloader() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void DevInfo::clear_bootloader() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.bootloader_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& DevInfo::bootloader() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.bootloader)
  return _internal_bootloader();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_bootloader(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.bootloader_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.bootloader)
}
inline std::string* DevInfo::mutable_bootloader() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_bootloader();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.bootloader)
  return _s;
}
inline const std::string& DevInfo::_internal_bootloader() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.bootloader_.Get();
}
inline void DevInfo::_internal_set_bootloader(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.bootloader_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_bootloader() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.bootloader_.Mutable( GetArena());
}
inline std::string* DevInfo::release_bootloader() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.bootloader)
  if ((_impl_._has_bits_[0] & 0x00000001u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* released = _impl_.bootloader_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.bootloader_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_bootloader(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.bootloader_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.bootloader_.IsDefault()) {
          _impl_.bootloader_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.bootloader)
}

// optional bytes procVersion = 2;
inline bool DevInfo::has_procversion() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline void DevInfo::clear_procversion() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.procversion_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline const std::string& DevInfo::procversion() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.procVersion)
  return _internal_procversion();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_procversion(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.procversion_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.procVersion)
}
inline std::string* DevInfo::mutable_procversion() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_procversion();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.procVersion)
  return _s;
}
inline const std::string& DevInfo::_internal_procversion() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.procversion_.Get();
}
inline void DevInfo::_internal_set_procversion(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.procversion_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_procversion() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  return _impl_.procversion_.Mutable( GetArena());
}
inline std::string* DevInfo::release_procversion() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.procVersion)
  if ((_impl_._has_bits_[0] & 0x00000002u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000002u;
  auto* released = _impl_.procversion_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.procversion_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_procversion(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }
  _impl_.procversion_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.procversion_.IsDefault()) {
          _impl_.procversion_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.procVersion)
}

// optional bytes codename = 3;
inline bool DevInfo::has_codename() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline void DevInfo::clear_codename() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.codename_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline const std::string& DevInfo::codename() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.codename)
  return _internal_codename();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_codename(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.codename_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.codename)
}
inline std::string* DevInfo::mutable_codename() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_codename();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.codename)
  return _s;
}
inline const std::string& DevInfo::_internal_codename() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.codename_.Get();
}
inline void DevInfo::_internal_set_codename(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.codename_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_codename() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000004u;
  return _impl_.codename_.Mutable( GetArena());
}
inline std::string* DevInfo::release_codename() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.codename)
  if ((_impl_._has_bits_[0] & 0x00000004u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000004u;
  auto* released = _impl_.codename_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.codename_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_codename(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000004u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000004u;
  }
  _impl_.codename_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.codename_.IsDefault()) {
          _impl_.codename_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.codename)
}

// optional bytes incremental = 4;
inline bool DevInfo::has_incremental() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline void DevInfo::clear_incremental() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.incremental_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline const std::string& DevInfo::incremental() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.incremental)
  return _internal_incremental();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_incremental(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.incremental_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.incremental)
}
inline std::string* DevInfo::mutable_incremental() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_incremental();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.incremental)
  return _s;
}
inline const std::string& DevInfo::_internal_incremental() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.incremental_.Get();
}
inline void DevInfo::_internal_set_incremental(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.incremental_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_incremental() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000008u;
  return _impl_.incremental_.Mutable( GetArena());
}
inline std::string* DevInfo::release_incremental() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.incremental)
  if ((_impl_._has_bits_[0] & 0x00000008u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000008u;
  auto* released = _impl_.incremental_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.incremental_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_incremental(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000008u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000008u;
  }
  _impl_.incremental_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.incremental_.IsDefault()) {
          _impl_.incremental_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.incremental)
}

// optional bytes fingerprint = 5;
inline bool DevInfo::has_fingerprint() const {
  bool value = (_impl_._has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline void DevInfo::clear_fingerprint() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.fingerprint_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000010u;
}
inline const std::string& DevInfo::fingerprint() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.fingerprint)
  return _internal_fingerprint();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_fingerprint(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000010u;
  _impl_.fingerprint_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.fingerprint)
}
inline std::string* DevInfo::mutable_fingerprint() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_fingerprint();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.fingerprint)
  return _s;
}
inline const std::string& DevInfo::_internal_fingerprint() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.fingerprint_.Get();
}
inline void DevInfo::_internal_set_fingerprint(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000010u;
  _impl_.fingerprint_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_fingerprint() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000010u;
  return _impl_.fingerprint_.Mutable( GetArena());
}
inline std::string* DevInfo::release_fingerprint() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.fingerprint)
  if ((_impl_._has_bits_[0] & 0x00000010u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000010u;
  auto* released = _impl_.fingerprint_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.fingerprint_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_fingerprint(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000010u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000010u;
  }
  _impl_.fingerprint_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.fingerprint_.IsDefault()) {
          _impl_.fingerprint_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.fingerprint)
}

// optional bytes bootId = 6;
inline bool DevInfo::has_bootid() const {
  bool value = (_impl_._has_bits_[0] & 0x00000020u) != 0;
  return value;
}
inline void DevInfo::clear_bootid() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.bootid_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000020u;
}
inline const std::string& DevInfo::bootid() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.bootId)
  return _internal_bootid();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_bootid(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000020u;
  _impl_.bootid_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.bootId)
}
inline std::string* DevInfo::mutable_bootid() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_bootid();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.bootId)
  return _s;
}
inline const std::string& DevInfo::_internal_bootid() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.bootid_.Get();
}
inline void DevInfo::_internal_set_bootid(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000020u;
  _impl_.bootid_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_bootid() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000020u;
  return _impl_.bootid_.Mutable( GetArena());
}
inline std::string* DevInfo::release_bootid() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.bootId)
  if ((_impl_._has_bits_[0] & 0x00000020u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000020u;
  auto* released = _impl_.bootid_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.bootid_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_bootid(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000020u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000020u;
  }
  _impl_.bootid_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.bootid_.IsDefault()) {
          _impl_.bootid_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.bootId)
}

// optional bytes androidId = 7;
inline bool DevInfo::has_androidid() const {
  bool value = (_impl_._has_bits_[0] & 0x00000040u) != 0;
  return value;
}
inline void DevInfo::clear_androidid() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.androidid_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000040u;
}
inline const std::string& DevInfo::androidid() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.androidId)
  return _internal_androidid();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_androidid(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000040u;
  _impl_.androidid_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.androidId)
}
inline std::string* DevInfo::mutable_androidid() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_androidid();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.androidId)
  return _s;
}
inline const std::string& DevInfo::_internal_androidid() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.androidid_.Get();
}
inline void DevInfo::_internal_set_androidid(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000040u;
  _impl_.androidid_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_androidid() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000040u;
  return _impl_.androidid_.Mutable( GetArena());
}
inline std::string* DevInfo::release_androidid() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.androidId)
  if ((_impl_._has_bits_[0] & 0x00000040u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000040u;
  auto* released = _impl_.androidid_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.androidid_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_androidid(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000040u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000040u;
  }
  _impl_.androidid_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.androidid_.IsDefault()) {
          _impl_.androidid_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.androidId)
}

// optional bytes baseBand = 8;
inline bool DevInfo::has_baseband() const {
  bool value = (_impl_._has_bits_[0] & 0x00000080u) != 0;
  return value;
}
inline void DevInfo::clear_baseband() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.baseband_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000080u;
}
inline const std::string& DevInfo::baseband() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.baseBand)
  return _internal_baseband();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_baseband(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000080u;
  _impl_.baseband_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.baseBand)
}
inline std::string* DevInfo::mutable_baseband() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_baseband();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.baseBand)
  return _s;
}
inline const std::string& DevInfo::_internal_baseband() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.baseband_.Get();
}
inline void DevInfo::_internal_set_baseband(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000080u;
  _impl_.baseband_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_baseband() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000080u;
  return _impl_.baseband_.Mutable( GetArena());
}
inline std::string* DevInfo::release_baseband() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.baseBand)
  if ((_impl_._has_bits_[0] & 0x00000080u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000080u;
  auto* released = _impl_.baseband_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.baseband_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_baseband(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000080u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000080u;
  }
  _impl_.baseband_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.baseband_.IsDefault()) {
          _impl_.baseband_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.baseBand)
}

// optional bytes innerVersion = 9;
inline bool DevInfo::has_innerversion() const {
  bool value = (_impl_._has_bits_[0] & 0x00000100u) != 0;
  return value;
}
inline void DevInfo::clear_innerversion() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.innerversion_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000100u;
}
inline const std::string& DevInfo::innerversion() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Flee.DevInfo.innerVersion)
  return _internal_innerversion();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void DevInfo::set_innerversion(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000100u;
  _impl_.innerversion_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Flee.DevInfo.innerVersion)
}
inline std::string* DevInfo::mutable_innerversion() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_innerversion();
  // @@protoc_insertion_point(field_mutable:Flee.DevInfo.innerVersion)
  return _s;
}
inline const std::string& DevInfo::_internal_innerversion() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.innerversion_.Get();
}
inline void DevInfo::_internal_set_innerversion(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000100u;
  _impl_.innerversion_.Set(value, GetArena());
}
inline std::string* DevInfo::_internal_mutable_innerversion() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000100u;
  return _impl_.innerversion_.Mutable( GetArena());
}
inline std::string* DevInfo::release_innerversion() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:Flee.DevInfo.innerVersion)
  if ((_impl_._has_bits_[0] & 0x00000100u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000100u;
  auto* released = _impl_.innerversion_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.innerversion_.Set("", GetArena());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void DevInfo::set_allocated_innerversion(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000100u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000100u;
  }
  _impl_.innerversion_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.innerversion_.IsDefault()) {
          _impl_.innerversion_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:Flee.DevInfo.innerVersion)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace Flee


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_DevInfo_2eproto_2epb_2eh
