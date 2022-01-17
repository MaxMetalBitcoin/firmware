
#include <cstdlib>
#include "mbtc_connector.h"

#include "Bitcoin.h"
#include "PSBT.h"

#include <string>

#ifdef __cplusplus
extern "C"
{
#endif
  char *mbtc_get_key(void)
  {
    HDPrivateKey hd("add good charge eagle walk culture book inherit fan nature seek repair", "");
    // derive native segwit account (bip-84) for tesnet
    HDPrivateKey account = hd.derive("m/84'/1'/0'/");
    // print xpub: vpub5YkPqVJTA7gjK...AH2rXvcAe3p781G
    HDPublicKey p = account.xpub();

    std::string str = p.address();

    return &str[0];
  }
#ifdef __cplusplus
}
#endif