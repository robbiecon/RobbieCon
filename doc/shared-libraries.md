Shared Libraries
================

## robbieconconsensus

The purpose of this library is to make the verification functionality that is critical to Robbiecon's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `robbieconconsensus.h` located in  `src/script/robbieconconsensus.h`.

#### Version

`robbieconconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`robbieconconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `robbieconconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `robbieconconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `robbieconconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/robbiecon/bips/blob/master/bip-0016.mediawiki)) subscripts
- `robbieconconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/robbiecon/bips/blob/master/bip-0066.mediawiki)) compliance
- `robbieconconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/robbiecon/bips/blob/master/bip-0147.mediawiki))
- `robbieconconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/robbiecon/bips/blob/master/bip-0065.mediawiki))
- `robbieconconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/robbiecon/bips/blob/master/bip-0112.mediawiki))
- `robbieconconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/robbiecon/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `robbieconconsensus_ERR_OK` - No errors with input parameters *(see the return value of `robbieconconsensus_verify_script` for the verification status)*
- `robbieconconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `robbieconconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `robbieconconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `robbieconconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NRobbiecon](https://github.com/NicolasDorier/NRobbiecon/blob/master/NRobbiecon/Script.cs#L814) (.NET Bindings)
- [node-librobbieconconsensus](https://github.com/bitpay/node-librobbieconconsensus) (Node.js Bindings)
- [java-librobbieconconsensus](https://github.com/dexX7/java-librobbieconconsensus) (Java Bindings)
- [robbieconconsensus-php](https://github.com/Bit-Wasp/robbieconconsensus-php) (PHP Bindings)
