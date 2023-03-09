#include "AccountSecrets.h"

namespace Flee {
AccountSecrets::AccountSecrets(uint32_t uin) {
    // hb480 未完成
    this->hb480 << uin;
}

AccountSecrets::AccountSecrets(const AccountSecrets& other)
    : seq(other.seq.load()),
      session(other.session),
      randkey(other.randkey),
      tgtgt(other.tgtgt),
      tgt(other.tgt),
      skey(other.skey),
      d2(other.d2),
      d2key(other.d2key),
      t104(other.t104),
      t174(other.t174),
      qrsig(other.qrsig),
      bigdata(other.bigdata),
      hb480(other.hb480),
      emp_time(other.emp_time),
      time_diff(other.time_diff) {}

int16_t AccountSecrets::seq_pp() {
    auto item = seq++;
    seq &= 0x7fff;
    return item;
}
}; // namespace Flee