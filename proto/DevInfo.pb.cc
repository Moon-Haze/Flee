// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DevInfo.proto

#include "DevInfo.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace Flee {

inline constexpr DevInfo::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        bootloader_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        procversion_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        codename_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        incremental_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        fingerprint_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        bootid_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        androidid_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        baseband_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        innerversion_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()) {}

template <typename>
PROTOBUF_CONSTEXPR DevInfo::DevInfo(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct DevInfoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR DevInfoDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~DevInfoDefaultTypeInternal() {}
  union {
    DevInfo _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 DevInfoDefaultTypeInternal _DevInfo_default_instance_;
}  // namespace Flee
static ::_pb::Metadata file_level_metadata_DevInfo_2eproto[1];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_DevInfo_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_DevInfo_2eproto = nullptr;
const ::uint32_t TableStruct_DevInfo_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_._has_bits_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.bootloader_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.procversion_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.codename_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.incremental_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.fingerprint_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.bootid_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.androidid_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.baseband_),
    PROTOBUF_FIELD_OFFSET(::Flee::DevInfo, _impl_.innerversion_),
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        {0, 17, -1, sizeof(::Flee::DevInfo)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::Flee::_DevInfo_default_instance_._instance,
};
const char descriptor_table_protodef_DevInfo_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\rDevInfo.proto\022\004Flee\"\351\002\n\007DevInfo\022\027\n\nboo"
    "tloader\030\001 \001(\014H\000\210\001\001\022\030\n\013procVersion\030\002 \001(\014H"
    "\001\210\001\001\022\025\n\010codename\030\003 \001(\014H\002\210\001\001\022\030\n\013increment"
    "al\030\004 \001(\014H\003\210\001\001\022\030\n\013fingerprint\030\005 \001(\014H\004\210\001\001\022"
    "\023\n\006bootId\030\006 \001(\014H\005\210\001\001\022\026\n\tandroidId\030\007 \001(\014H"
    "\006\210\001\001\022\025\n\010baseBand\030\010 \001(\014H\007\210\001\001\022\031\n\014innerVers"
    "ion\030\t \001(\014H\010\210\001\001B\r\n\013_bootloaderB\016\n\014_procVe"
    "rsionB\013\n\t_codenameB\016\n\014_incrementalB\016\n\014_f"
    "ingerprintB\t\n\007_bootIdB\014\n\n_androidIdB\013\n\t_"
    "baseBandB\017\n\r_innerVersionb\006proto3"
};
static ::absl::once_flag descriptor_table_DevInfo_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_DevInfo_2eproto = {
    false,
    false,
    393,
    descriptor_table_protodef_DevInfo_2eproto,
    "DevInfo.proto",
    &descriptor_table_DevInfo_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_DevInfo_2eproto::offsets,
    file_level_metadata_DevInfo_2eproto,
    file_level_enum_descriptors_DevInfo_2eproto,
    file_level_service_descriptors_DevInfo_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_DevInfo_2eproto_getter() {
  return &descriptor_table_DevInfo_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_DevInfo_2eproto(&descriptor_table_DevInfo_2eproto);
namespace Flee {
// ===================================================================

class DevInfo::_Internal {
 public:
  using HasBits = decltype(std::declval<DevInfo>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(DevInfo, _impl_._has_bits_);
  static void set_has_bootloader(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_procversion(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_codename(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_incremental(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_fingerprint(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static void set_has_bootid(HasBits* has_bits) {
    (*has_bits)[0] |= 32u;
  }
  static void set_has_androidid(HasBits* has_bits) {
    (*has_bits)[0] |= 64u;
  }
  static void set_has_baseband(HasBits* has_bits) {
    (*has_bits)[0] |= 128u;
  }
  static void set_has_innerversion(HasBits* has_bits) {
    (*has_bits)[0] |= 256u;
  }
};

DevInfo::DevInfo(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:Flee.DevInfo)
}
inline PROTOBUF_NDEBUG_INLINE DevInfo::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : _has_bits_{from._has_bits_},
        _cached_size_{0},
        bootloader_(arena, from.bootloader_),
        procversion_(arena, from.procversion_),
        codename_(arena, from.codename_),
        incremental_(arena, from.incremental_),
        fingerprint_(arena, from.fingerprint_),
        bootid_(arena, from.bootid_),
        androidid_(arena, from.androidid_),
        baseband_(arena, from.baseband_),
        innerversion_(arena, from.innerversion_) {}

DevInfo::DevInfo(
    ::google::protobuf::Arena* arena,
    const DevInfo& from)
    : ::google::protobuf::Message(arena) {
  DevInfo* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);

  // @@protoc_insertion_point(copy_constructor:Flee.DevInfo)
}
inline PROTOBUF_NDEBUG_INLINE DevInfo::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0},
        bootloader_(arena),
        procversion_(arena),
        codename_(arena),
        incremental_(arena),
        fingerprint_(arena),
        bootid_(arena),
        androidid_(arena),
        baseband_(arena),
        innerversion_(arena) {}

inline void DevInfo::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
DevInfo::~DevInfo() {
  // @@protoc_insertion_point(destructor:Flee.DevInfo)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void DevInfo::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.bootloader_.Destroy();
  _impl_.procversion_.Destroy();
  _impl_.codename_.Destroy();
  _impl_.incremental_.Destroy();
  _impl_.fingerprint_.Destroy();
  _impl_.bootid_.Destroy();
  _impl_.androidid_.Destroy();
  _impl_.baseband_.Destroy();
  _impl_.innerversion_.Destroy();
  _impl_.~Impl_();
}

PROTOBUF_NOINLINE void DevInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:Flee.DevInfo)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x000000ffu) {
    if (cached_has_bits & 0x00000001u) {
      _impl_.bootloader_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      _impl_.procversion_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000004u) {
      _impl_.codename_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000008u) {
      _impl_.incremental_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000010u) {
      _impl_.fingerprint_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000020u) {
      _impl_.bootid_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000040u) {
      _impl_.androidid_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000080u) {
      _impl_.baseband_.ClearNonDefaultToEmpty();
    }
  }
  if (cached_has_bits & 0x00000100u) {
    _impl_.innerversion_.ClearNonDefaultToEmpty();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* DevInfo::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<4, 9, 0, 0, 2> DevInfo::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(DevInfo, _impl_._has_bits_),
    0, // no _extensions_
    9, 120,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294966784,  // skipmap
    offsetof(decltype(_table_), field_entries),
    9,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_DevInfo_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // optional bytes bootloader = 1;
    {::_pbi::TcParser::FastBS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.bootloader_)}},
    // optional bytes procVersion = 2;
    {::_pbi::TcParser::FastBS1,
     {18, 1, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.procversion_)}},
    // optional bytes codename = 3;
    {::_pbi::TcParser::FastBS1,
     {26, 2, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.codename_)}},
    // optional bytes incremental = 4;
    {::_pbi::TcParser::FastBS1,
     {34, 3, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.incremental_)}},
    // optional bytes fingerprint = 5;
    {::_pbi::TcParser::FastBS1,
     {42, 4, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.fingerprint_)}},
    // optional bytes bootId = 6;
    {::_pbi::TcParser::FastBS1,
     {50, 5, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.bootid_)}},
    // optional bytes androidId = 7;
    {::_pbi::TcParser::FastBS1,
     {58, 6, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.androidid_)}},
    // optional bytes baseBand = 8;
    {::_pbi::TcParser::FastBS1,
     {66, 7, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.baseband_)}},
    // optional bytes innerVersion = 9;
    {::_pbi::TcParser::FastBS1,
     {74, 8, 0, PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.innerversion_)}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
  }}, {{
    65535, 65535
  }}, {{
    // optional bytes bootloader = 1;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.bootloader_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes procVersion = 2;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.procversion_), _Internal::kHasBitsOffset + 1, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes codename = 3;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.codename_), _Internal::kHasBitsOffset + 2, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes incremental = 4;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.incremental_), _Internal::kHasBitsOffset + 3, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes fingerprint = 5;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.fingerprint_), _Internal::kHasBitsOffset + 4, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes bootId = 6;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.bootid_), _Internal::kHasBitsOffset + 5, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes androidId = 7;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.androidid_), _Internal::kHasBitsOffset + 6, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes baseBand = 8;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.baseband_), _Internal::kHasBitsOffset + 7, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
    // optional bytes innerVersion = 9;
    {PROTOBUF_FIELD_OFFSET(DevInfo, _impl_.innerversion_), _Internal::kHasBitsOffset + 8, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kBytes | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
  }},
};

::uint8_t* DevInfo::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Flee.DevInfo)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // optional bytes bootloader = 1;
  if (cached_has_bits & 0x00000001u) {
    const std::string& _s = this->_internal_bootloader();
    target = stream->WriteBytesMaybeAliased(1, _s, target);
  }

  // optional bytes procVersion = 2;
  if (cached_has_bits & 0x00000002u) {
    const std::string& _s = this->_internal_procversion();
    target = stream->WriteBytesMaybeAliased(2, _s, target);
  }

  // optional bytes codename = 3;
  if (cached_has_bits & 0x00000004u) {
    const std::string& _s = this->_internal_codename();
    target = stream->WriteBytesMaybeAliased(3, _s, target);
  }

  // optional bytes incremental = 4;
  if (cached_has_bits & 0x00000008u) {
    const std::string& _s = this->_internal_incremental();
    target = stream->WriteBytesMaybeAliased(4, _s, target);
  }

  // optional bytes fingerprint = 5;
  if (cached_has_bits & 0x00000010u) {
    const std::string& _s = this->_internal_fingerprint();
    target = stream->WriteBytesMaybeAliased(5, _s, target);
  }

  // optional bytes bootId = 6;
  if (cached_has_bits & 0x00000020u) {
    const std::string& _s = this->_internal_bootid();
    target = stream->WriteBytesMaybeAliased(6, _s, target);
  }

  // optional bytes androidId = 7;
  if (cached_has_bits & 0x00000040u) {
    const std::string& _s = this->_internal_androidid();
    target = stream->WriteBytesMaybeAliased(7, _s, target);
  }

  // optional bytes baseBand = 8;
  if (cached_has_bits & 0x00000080u) {
    const std::string& _s = this->_internal_baseband();
    target = stream->WriteBytesMaybeAliased(8, _s, target);
  }

  // optional bytes innerVersion = 9;
  if (cached_has_bits & 0x00000100u) {
    const std::string& _s = this->_internal_innerversion();
    target = stream->WriteBytesMaybeAliased(9, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Flee.DevInfo)
  return target;
}

::size_t DevInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Flee.DevInfo)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x000000ffu) {
    // optional bytes bootloader = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_bootloader());
    }

    // optional bytes procVersion = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_procversion());
    }

    // optional bytes codename = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_codename());
    }

    // optional bytes incremental = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_incremental());
    }

    // optional bytes fingerprint = 5;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_fingerprint());
    }

    // optional bytes bootId = 6;
    if (cached_has_bits & 0x00000020u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_bootid());
    }

    // optional bytes androidId = 7;
    if (cached_has_bits & 0x00000040u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_androidid());
    }

    // optional bytes baseBand = 8;
    if (cached_has_bits & 0x00000080u) {
      total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                      this->_internal_baseband());
    }

  }
  // optional bytes innerVersion = 9;
  if (cached_has_bits & 0x00000100u) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::BytesSize(
                                    this->_internal_innerversion());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::google::protobuf::Message::ClassData DevInfo::_class_data_ = {
    DevInfo::MergeImpl,
    nullptr,  // OnDemandRegisterArenaDtor
};
const ::google::protobuf::Message::ClassData* DevInfo::GetClassData() const {
  return &_class_data_;
}

void DevInfo::MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg) {
  auto* const _this = static_cast<DevInfo*>(&to_msg);
  auto& from = static_cast<const DevInfo&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Flee.DevInfo)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x000000ffu) {
    if (cached_has_bits & 0x00000001u) {
      _this->_internal_set_bootloader(from._internal_bootloader());
    }
    if (cached_has_bits & 0x00000002u) {
      _this->_internal_set_procversion(from._internal_procversion());
    }
    if (cached_has_bits & 0x00000004u) {
      _this->_internal_set_codename(from._internal_codename());
    }
    if (cached_has_bits & 0x00000008u) {
      _this->_internal_set_incremental(from._internal_incremental());
    }
    if (cached_has_bits & 0x00000010u) {
      _this->_internal_set_fingerprint(from._internal_fingerprint());
    }
    if (cached_has_bits & 0x00000020u) {
      _this->_internal_set_bootid(from._internal_bootid());
    }
    if (cached_has_bits & 0x00000040u) {
      _this->_internal_set_androidid(from._internal_androidid());
    }
    if (cached_has_bits & 0x00000080u) {
      _this->_internal_set_baseband(from._internal_baseband());
    }
  }
  if (cached_has_bits & 0x00000100u) {
    _this->_internal_set_innerversion(from._internal_innerversion());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void DevInfo::CopyFrom(const DevInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Flee.DevInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool DevInfo::IsInitialized() const {
  return true;
}

::_pbi::CachedSize* DevInfo::AccessCachedSize() const {
  return &_impl_._cached_size_;
}
void DevInfo::InternalSwap(DevInfo* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.bootloader_, &other->_impl_.bootloader_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.procversion_, &other->_impl_.procversion_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.codename_, &other->_impl_.codename_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.incremental_, &other->_impl_.incremental_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.fingerprint_, &other->_impl_.fingerprint_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.bootid_, &other->_impl_.bootid_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.androidid_, &other->_impl_.androidid_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.baseband_, &other->_impl_.baseband_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.innerversion_, &other->_impl_.innerversion_, arena);
}

::google::protobuf::Metadata DevInfo::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_DevInfo_2eproto_getter, &descriptor_table_DevInfo_2eproto_once,
      file_level_metadata_DevInfo_2eproto[0]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace Flee
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"