// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2009-2016 The Robbiecon Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "WSJ 18/Nov/2016 11h20m am ET Charitable Giving Is Up, But Only Among the Wealthy 1479531295";
    const CScript genesisOutputScript = CScript() << ParseHex( "0471cefc101c0e51c1066ca77fc430131b94ef7275710087c00d5f96afb25f259606613b3d0d0121c7a2dc5b2fa9b3b70fe3a7c8243411b0ae9b34ce5d00441d8e") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 227931;
        consensus.BIP34Hash = uint256S("0x000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8");
        consensus.BIP65Height = 388381; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP66Height = 363725; // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 99 * 60; // two weeks    original: 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 3 * 60;	// 6*60seconds, every new block, orig 10*60
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 31; // 94% of 33   original: 196 => 95% of 2016
        consensus.nMinerConfirmationWindow = 33; // orig: 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1479531295; // GMT: Sat, 19 Nov 2016 04:54:55 GMT
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764799; // GMT: Sun, 31 Dec 2017 23:59:59 GMT

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1479531296; // GMT: Sat, 19 Nov 2016 04:54:56 GMT
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1511067296; // GMT: Sat, 19 Nov 2017 04:54:56 GMT

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1479531297; // GMT: Sat, 19 Nov 2016 04:54:57 GMT
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1511067297; // GMT: Sat, 19 Nov 2017 04:54:57 GMT

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000002cb971dd56d1c583c20f90");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xc6;
        pchMessageStart[1] = 0xe8;
        pchMessageStart[2] = 0xfa;
        pchMessageStart[3] = 0x22;
        nDefaultPort = 9663;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1479540402, 2136447534, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000000a5ce1b8a36b6ccc7ea26a3d3fb1520776a8e6c4591d1b9fa1b535da4"));
        assert(genesis.hashMerkleRoot == uint256S("0x97b5d80a5a8d0aa327264e8fc9bbeb40469987fff0f69df67a129e6873d65a07"));

        // Note that of those with the service bits flag, most only support a subset of possible options
		vSeeds.push_back(CDNSSeedData("seed1.robbiecon.cc", "seed1.robbiecon.cc", true)); // Robbie Con, only supports x1, x5, x9, and xd
		vSeeds.push_back(CDNSSeedData("seed2.robbiecon.cc", "seed2.robbiecon.cc", true)); // Robbie Con
		vSeeds.push_back(CDNSSeedData("difacturo.com", "difacturo.com", true)); 			// difacturo
		vSeeds.push_back(CDNSSeedData("52.28.209.234", "52.28.209.234", true)); // difacturo

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60); // Dez: 60-61 Letter: R, hex: 0x3c-0x3d, orig dez 0.
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,122); // Dez: 122-123 Letter: r HEX: 0x7a-0x7b, orig dez 5
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,93); // Dez: 92-93 Letter: e HEX: 0x5c-0x5d orig dez 128
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x09)(0x33)(0xF1)(0x3C).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x09)(0x33)(0xD2)(0xC4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0x00000000a5ce1b8a36b6ccc7ea26a3d3fb1520776a8e6c4591d1b9fa1b535da4")),
            		 0, 			// * UNIX timestamp of last checkpoint block
                     0,   		    // * total number of transactions between genesis and last checkpoint
					            	//   (the tx=... number in the SetBestChain debug.log lines)
            	1000.0     			// * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 21111;
        consensus.BIP34Hash = uint256S("0x0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8");
        consensus.BIP65Height = 581885; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 330776; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1479531298; // GMT: Sat, 19 Nov 2016 04:54:58 GMT
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764799; // GMT: Sun, 31 Dec 2017 23:59:59 GMT

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1479531299; // GMT: Sat, 19 Nov 2016 04:54:59 GMT
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1511067299; // GMT: Sat, 19 Nov 2016 04:54:59 GMT

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1479531300; // GMT: Sat, 19 Nov 2016 04:55:00 GMT
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1511067300; // GMT: Sat, 19 Nov 2017 04:55:00 GMT

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000198b4def2baa9338d6");

        pchMessageStart[0] = 0x66;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0x30;
        pchMessageStart[3] = 0x21;
        nDefaultPort = 19663;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1479572354, 2579207759, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000000046670c36a266a73b70069925970e7b1afc5ea00f3bbcf439adff8674"));
        assert(genesis.hashMerkleRoot == uint256S("0x97b5d80a5a8d0aa327264e8fc9bbeb40469987fff0f69df67a129e6873d65a07"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
		vSeeds.push_back(CDNSSeedData("testnet1.robbiecon.cc", "testnet1.robbiecon.cc", true)); // Robbie Con
		vSeeds.push_back(CDNSSeedData("testnet2.robbiecon.cc", "testnet2.robbiecon.cc", true)); // Robbie Con

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,104); // Dez 104 Letter: i or j Hex: 0x68 Orig Dez: 111
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,165); // Dez 165 Letter: 2 Hex: 0xa5 Orig Dez: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,231); // Dez 231 Letter: 2 Hex: 0xe7 Orig Dez: 239
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x09)(0x66)(0x33)(0x11).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x09)(0x66)(0x7A)(0x3B).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("0000000046670c36a266a73b70069925970e7b1afc5ea00f3bbcf439adff8674")),
            0, 			// * UNIX timestamp of last checkpoint block
            0,   		// * total number of transactions between genesis and last checkpoint
						//   (the tx=... number in the SetBestChain debug.log lines)
            100     	// * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0x4a;
        pchMessageStart[2] = 0x93;
        pchMessageStart[3] = 0x1f;
        nDefaultPort = 19774;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1479540614, 2, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x740145d3c990485b3117d7532ab7922ce04e9488c8d37dcb7f1164417deead9a"));
        assert(genesis.hashMerkleRoot == uint256S("0x97b5d80a5a8d0aa327264e8fc9bbeb40469987fff0f69df67a129e6873d65a07"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("740145d3c990485b3117d7532ab7922ce04e9488c8d37dcb7f1164417deead9a")),
            0, 			// * UNIX timestamp of last checkpoint block
            0,   		// * total number of transactions between genesis and last checkpoint
						//   (the tx=... number in the SetBestChain debug.log lines)
            0     		// * estimated number of transactions per day after checkpoint
        };
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,104); // Dez 104 Letter: i or j Hex: 0x68 Orig Dez: 111
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,165); // Dez 165 Letter: 2 Hex: 0xa5 Orig Dez: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,231); // Dez 231 Letter: 2 Hex: 0xe7 Orig Dez: 239
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x09)(0x66)(0x33)(0x11).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x09)(0x66)(0x7A)(0x3B).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 
