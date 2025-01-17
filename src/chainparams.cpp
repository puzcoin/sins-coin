// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2019 The SafeInsure Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */


static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000130c84f57a7c493014d1ce1820ded6372846da945b44b170c453499d796"))
    (24550, uint256("23222f0b00b7b28248eefc81ebe56194b5a961c3be4fe09ec3030b205b3efd55"))
    (89875, uint256("ff4960011b696074be79cb9ddce78a375553e2ecb0faf608e2d5c05845be76fd"))
    (160790, uint256("d4626532c209ef9363af91701d1a2b36573a9b949b4e8a7898d1965b76119ae4"))    
    (185125, uint256("16990263ea82bd67b4b37b5e5daa27ee51266b4a3bb4a7b2836e343320b8eb34"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1548333284,  // * UNIX timestamp of last checkpoint block
    588088,      // * total number of transactions between genesis and last checkpoint
                 //   (the tx=... number in the SetBestChain debug.log lines)
    2000         // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1537178400,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1537178400,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        pchMessageStart[0] = 0x42;
        pchMessageStart[1] = 0x4a;
        pchMessageStart[2] = 0xe7;
        pchMessageStart[3] = 0x91;
        vAlertPubKey = ParseHex("04678f93351301f0209dcfd023fe0f2a58085e56a7bb0936b32e4de73f242277cf402d3995a551276762d42de4e20e1df96bb999959d3436fe38a1a58c3b8f863d");
        nDefaultPort = 30105;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // SafeInsure starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 525600; // one year
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SafeInsure: every block
        nTargetSpacing = 1 * 60;  // SafeInsure: 1 minute
        nLastPOWBlock = 310;
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21000000 * COIN;
        nMasternodeCollateral = 1000; 

        const char* pszTimestamp = "Every Generation Gets the Beach Villain It Deserves";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("044d6a429ce3186c325bf496749e7f91399624e1ca5ff0f8fa8e37e6fc8d1565b9a3a00f559ed6d18a82f7cb5b4602307b5cf610bc4e83b7ef6347fa9b557dd341") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1537178400;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 4391468;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000130c84f57a7c493014d1ce1820ded6372846da945b44b170c453499d796"));
        assert(genesis.hashMerkleRoot == uint256("0x4c0b221ab5d5e2a22efe8cc6aceed7a81b11e145f05988740cd6de38efc4be1f"));

        vSeeds.push_back(CDNSSeedData("node1", "45.249.244.140"));		
	vSeeds.push_back(CDNSSeedData("node2", "152.32.129.164"));
	vSeeds.push_back(CDNSSeedData("node3", "207.148.127.109"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63); // Safeinsure addresses start with 'S'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 20); // Safeinsure script addresses start with '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 140);    // Safeinsure private keys start with 'y'
		// SafeInsure BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		// SafeInsure BIP32 pubkeys start with 'xprv' (Bitcoin defaults)		
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is '0X80000a00' from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x0a)(0x00).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0498cefbfb4d43f2e7338f2ef625fb2ca7c67cf9bab86ddb57f18b61bb883fa22112b58ed6440caa019cbec5cab2d92e983b7f9aa620b6184d71347304ff285ade";
        strPrivatesendPoolDummyAddress = "SPNh5Ri9yyvsx86bRFs8frosqUL2UG3PLv";
        nStartMasternodePayments = 1537178400;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0x6e;
        pchMessageStart[2] = 0x23;
        pchMessageStart[3] = 0xad;
        vAlertPubKey = ParseHex("04ad29797167d7fa1fc1943325e3aac7b36de3c8cf0ad8f4743459d4942f7f034aa7e8748f2e95f80e44b280c5216bfa4ec2207e0d042d86e2fb59d2890c993e30");
        nDefaultPort = 39107;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // SafeInsure: 1 day
        nTargetSpacing = 1 * 60;  // SafeInsure: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1537178400;
        genesis.nNonce = 5047298;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000a15cee886438566bd86131a3d16490c8463ae1b19399371e21b66c09069"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("node1", "45.249.244.140"));
	vSeeds.push_back(CDNSSeedData("node2", "152.32.129.164"));
	vSeeds.push_back(CDNSSeedData("node3", "207.148.127.109"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127); // Testnet safeinsure addresses start with 't'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 20);  // Testnet safeinsure script addresses start with '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
		// SafeInsure BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		// SafeInsure BIP32 pubkeys start with 'xprv' (Bitcoin defaults)		
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // Testnet safeinsure BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0446df557f7776e4d980f8f996813e59edaa2de3c29d9a54972ae664c02f1112c9665f65809a452a3c4223457ec5650dafb3b9af1792ec680ad74bd3e1f9d30020";
        strPrivatesendPoolDummyAddress = "ScALrhPCym7kCE4AnGHL8mfzhzAAwspvLD";
        nStartMasternodePayments = 1537178400;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xba;
        pchMessageStart[1] = 0x21;
        pchMessageStart[2] = 0x9d;
        pchMessageStart[3] = 0x2f;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // SafeInsure: 1 day
        nTargetSpacing = 1 * 60;        // SafeInsure: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1537178400;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2052;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 39109;
        assert(hashGenesisBlock == uint256("0x57933e338b5f5776f1e836090e44c9bd21c5c16a3c7cb1851d861d0996ef9635"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 39111;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
