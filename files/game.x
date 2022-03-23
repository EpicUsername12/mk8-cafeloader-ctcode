SECTIONS {

    MK8_OSDynLoad_Acquire = 0x0249E744;
    MK8_OSDynLoad_FindExport = 0x02678828;

    /* Memory functions */
    __nw__FUi = 0x027216B4;
	__nwa__FUi = 0x027217EC;
    __nw__FUiPQ2_4sead4Heapi = 0x027219F4;
	__nwa__FUiPQ2_4sead4Heapi = 0x02721A78;
	__dl__FPv = 0x027218E4;
	__dla__FPv = 0x0272196C;
    __memzero = 0x02A8C3A0;

    /* std mk8 functions */
    _Xran__Q2_3std12_String_baseCFv = 0x02A86264;
    _Xlen__Q2_3std12_String_baseCFv = 0x02A8679C;
    _Raise_handler__3std = 0x101A9DDC;
    _Throw__3stdFRCQ2_3std9exception = 0x02A861C8;
    wcslen = 0x02A8794C;
    atoi = 0x02A8A814;

    /* C++ GHS functions */
    __pure_virtual_called = 0x02A86D90;
	__deleted_virtual_called = 0x02A86E18;
	__vec_new = 0x02A86A88;
    __record_needed_destruction = 0x02A86D18;
    __gh_udiv64 = 0x029343D4;
    __gh_float_printf = 0x02A881DC;

    /* sead::HeapMgr */
    sInstancePtr__Q2_4sead7HeapMgr = 0x1018C7CC;
    getCurrentHeap__Q2_4sead7HeapMgrCFv = 0x0273D1AC;

    /* sead::Heap and childs */
    sRootHeaps__Q2_4sead7HeapMgr = 0x10205964;
    sIndependentHeaps__Q2_4sead7HeapMgr = 0x102059BC;
    setCurrentHeap___Q2_4sead7HeapMgrFPQ2_4sead4Heap = 0x0273D294;
    __ct__Q2_4sead8UnitHeapFRCQ2_4sead23SafeStringBase__tm__2_cPQ2_4sead4HeapPvUiT4b = 0x0273D420;
    tryCreate__Q2_4sead7ExpHeapSFUiRCQ2_4sead23SafeStringBase__tm__2_cPQ2_4sead4HeapQ3_4sead4Heap13HeapDirectionb = 0x0273A128;
    tryCreate__Q2_4sead7ExpHeapSFPvUiRCQ2_4sead23SafeStringBase__tm__2_cb = 0x0273A260;

    /* MK8 globals */
    gCupPaneNames = 0x100DC77C;
    gCupNames__Q2_2ui4ECup = 0x100D3E84;
    gTrackPaths = 0x101ab678;

    /* nw::lyt functions */
    LoadTexture__Q2_2nw3lytFPQ3_2nw3lyt11TextureInfoPCvUi = 0x026A0F04;
    setVisible__Q3_2nw3lyt4PaneFb = 0x0;
    s_pAllocator__Q3_2nw3lyt6Layout = 0x1018C150;

    /* net::NetworkEngine */
    registTransporter___Q2_3net13NetworkEngineFv = 0x023DFFD8;

    /* net::NetworkTransporter_CTGP */
    getVoteResultIndex__Q2_3net23NetworkTransporter_MenuCFv = 0x02411FF0;

    /* enl::Framework */
    sFrameworkInstance__Q2_3enl9Framework = 0x101A8EC4;

    /* enl::Buffer */
    clear__Q2_3enl6BufferFv = 0x028CF158;
    set__Q2_3enl6BufferFPCUcUi = 0x028CF228;
    __ct__Q2_3enl6BufferFPUcUi = 0x028CF198;

    /* sead::BufferedSafeStringBase */
    appendWithFormat__S__Q2_4sead31BufferedSafeStringBase__tm__2_cFPCZ1Ze_i = 0x02740D8C;
    format__S__Q2_4sead31BufferedSafeStringBase__tm__2_cFPCZ1Ze_i = 0x02740C68;

    /* sead::FileDeviceMgr */
    sInstance__Q2_4sead13FileDeviceMgr = 0x1018C788;
    tryOpen__Q2_4sead13FileDeviceMgrFPQ2_4sead10FileHandleRCQ2_4sead23SafeStringBase__tm__2_cQ3_4sead10FileDevice12FileOpenFlagUi = 0x027294F4;
    
    /* sead::FileDevice */
    tryOpenDirectory__Q2_4sead10FileDeviceFPQ2_4sead15DirectoryHandleRCQ2_4sead23SafeStringBase__tm__2_c = 0x02728950;
    tryReadDirectory__Q2_4sead10FileDeviceFPUiPQ2_4sead15DirectoryHandlePQ2_4sead14DirectoryEntryUi = 0x027289FC;
    tryCloseDirectory__Q2_4sead10FileDeviceFPQ2_4sead15DirectoryHandle = 0x02728364;

    /* sead::Stream */
    writeMemBlock__Q2_4sead11WriteStreamFPCvUi = 0x02749BD0;
    readMemBlock__Q2_4sead10ReadStreamFPvUi = 0x02749A7C;
    __dt__Q2_4sead6StreamFv = 0x02749C38;
    __ct__Q2_4sead6StreamFv = 0x02749894;

    /* sead::RamStream */
    __vtbl__Q2_4sead12RamStreamSrc = 0x1011ADDC;
    __dt__Q2_4sead12RamStreamSrcFv = 0x027494B0;

    /* enl::PeerManagerCommon */
    isHideClient__Q2_3enl17PeerManagerCommonCFv = 0x028DCEF4;
    getMyStationGroupArray__Q2_3enl17PeerManagerCommonCFv = 0x028D15E8;
    getConnectedNum__Q2_3enl17PeerManagerCommonCFv = 0x028DCB8C;
    getBufferIDByAID__Q2_3enl17PeerManagerCommonCFRCSc = 0x0200A3AC;
    getUniqueIDByAID__Q2_3enl17PeerManagerCommonCFRCSc = 0x0200A414;
    getBufferIDByUniqueID__Q2_3enl17PeerManagerCommonCFRCQ2_3enl8UniqueID = 0x028DCDDC;

    /* enl::TransportManager */
    isRequest__Q2_3enl16TransportManagerCFRCUc = 0x028D86E8;
    getContentTransporter__Q2_3enl16TransportManagerFRCUc = 0x028D7678;

    /* sead::IDisposer */
    __vtbl__Q2_4sead9IDisposer = 0x101014AC;
	__ct__Q2_4sead9IDisposerFv = 0x02739B64;
	__dt__Q2_4sead9IDisposerFv = 0x02739CCC;

    /* sead::PtrArrayImpl */
    allocBuffer__Q2_4sead12PtrArrayImplFiPQ2_4sead4HeapT1 = 0x02721F20;
    setBuffer__Q2_4sead12PtrArrayImplFiPv = 0x02721EFC;
    freeBuffer__Q2_4sead12PtrArrayImplFv = 0x02721F78;

    /* nw::lyt::MultiArcResourceAccessor */
    GetResource__Q3_2nw3lyt24MultiArcResourceAccessorFUiPCcPUi = 0x02694B70;

    /* sead::FileDevice */
    __CPR122__tryOpen__Q2_4sead10FileDeviceFPQ2_J12J10FileHandleRCQ2_J12J23SafeStringBase__tm__2_cQ3_J12JJ17J12FileOpenFlagUi = 0x02728470;
    tryGetFileSize__Q2_4sead10FileDeviceFPUiPQ2_4sead10FileHandle = 0x027288F0;
    tryClose__Q2_4sead10FileDeviceFPQ2_4sead10FileHandle = 0x027282A8;
    tryRead__Q2_4sead10FileDeviceFPUiPQ2_4sead10FileHandlePUcUi = 0x0272852C;

    /* sead::FileDeviceMgr */
    findDevice__Q2_4sead13FileDeviceMgrCFRCQ2_4sead23SafeStringBase__tm__2_c = 0x0272932C;
    tryLoad__Q2_4sead13FileDeviceMgrFRQ3_4sead10FileDevice7LoadArg = 0x027295A4;

    /* sys::SaveDataManager */
    getUserSaveDataPtr__Q2_3sys15SaveDataManagerFUc = 0x024F3630;

    /* sead::HashCRC32 */
    calcHash__Q2_4sead9HashCRC32SFPCvUi = 0x02721B60;

    /* sys::SystemEngine */
    getEngine__Q2_3sys12SystemEngineSFv = 0x024CE218;

    /* audio::utl */
    startSound2D__Q2_5audio3utlFPCc = 0x02048798;

    /* ui::UILoader */
    getHeap___Q2_2ui8UILoaderFi = 0x0253CC78;
    findMessage___Q2_2ui8UILoaderFi = 0x0253D194;

    /* ui::Input_Key */
    __ct__Q2_2ui9Input_KeyFv = 0x0253BF3C;

    /* ui::UIControl */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui9UIControlSFv = 0x101AB588;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui9UIControlSFv = 0x101B2AF0;
    setMessage__Q2_2ui9UIControlFRCQ2_4sead23SafeStringBase__tm__2_cPCw = 0x02536504;
    findPane__Q2_2ui9UIControlCFRCQ2_4sead23SafeStringBase__tm__2_c = 0x02531394;
    setTexture__Q2_2ui9UIControlFPQ3_2nw3lyt4PanePCQ3_2nw3lyt11TextureInfoUi = 0x025318D0;
    setVisible__Q2_2ui9UIControlFPQ3_2nw3lyt4Paneb = 0x02531858;
    setMessage__Q2_2ui9UIControlFPQ3_2nw3lyt4Panei = 0x025364C4;
    setMessage__Q2_2ui9UIControlFi = 0x02536428;
    __ct__Q2_2ui9UIControlFv = 0x02535A44;
    onFollowCursor__Q2_2ui9UIControlFPvi = 0x02535FB8;
    pushInput__Q2_2ui9UIControlFRQ2_2ui7UIInput = 0x02536114;
    createAnimator__Q2_2ui9UIControlFiT1 = 0x025360B8;

    /* ui::Control_Button */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui14Control_ButtonSFv = 0x101B2B3C;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui14Control_ButtonSFv = 0x101B2B40;
    onHandler__Q2_2ui14Control_ButtonFRCQ2_2ui7UIEvent = 0x02578ADC;
    __ct__Q2_2ui14Control_ButtonFv = 0x02578630;
    __ct__Q2_2ui12UICapTextureFv = 0x025341AC;
    getSLinkName__Q2_2ui14Control_ButtonFPQ2_4sead33FixedSafeString__tm__10_XCiL_2_64 = 0x02578B7C;
    __CPR113__getSLinkSeName__Q2_2ui14Control_ButtonFQ3_2uiJ22J7ESeTypePQ2_4sead33FixedSafeString__tm__10_XCiL_2_32 = 0x02578C14;
    __CPR63__startSe___Q2_2ui14Control_ButtonFQ3_2uiJ16J7ESeType = 0x02578EE8;
    selectOn__Q2_2ui14Control_ButtonFRCQ2_2ui7UIEvent = 0x02578C14;
    selectOff__Q2_2ui14Control_ButtonFRCQ2_2ui7UIEvent = 0x02578F90;
    decide__Q2_2ui14Control_ButtonFRCQ2_2ui7UIEvent = 0x02579014;
    unk3__Q2_2ui14Control_ButtonFv = 0x02A86E18;
    cancel__Q2_2ui14Control_ButtonFi = 0x025790EC;
    unk4__Q2_2ui14Control_ButtonFv = 0x02580BE8;
    unk5__Q2_2ui14Control_ButtonFv = 0x02580BF0;
    unk6__Q2_2ui14Control_ButtonFv = 0x02A86E18;
    unk7__Q2_2ui14Control_ButtonFv = 0x02A86E18;
    unk8__Q2_2ui14Control_ButtonFv = 0x02A86E18;
    unk9__Q2_2ui14Control_ButtonFv = 0x02A86E18;
    animOn__Q2_2ui14Control_ButtonFv = 0x02579170;
    animOff__Q2_2ui14Control_ButtonFv = 0x02579260;
    animKeepOn__Q2_2ui14Control_ButtonFv = 0x02579350;
    animKeepOff__Q2_2ui14Control_ButtonFv = 0x025793E8;
    animDecide__Q2_2ui14Control_ButtonFv = 0x02579490;
    animCancel__Q2_2ui14Control_ButtonFv = 0x02579534;
    __dt__Q2_2ui14Control_ButtonFv = 0x02578534;

    /* ui::Control_WifiCmnButton */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui21Control_WifiCmnButtonSFv = 0x101B2B68;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui21Control_WifiCmnButtonSFv = 0x101B2EAC;
    __vtbl__42Q2_4sead9IDisposer__Q2_2ui14Control_Button__Q2_2ui21Control_WifiCmnButton = 0x100D5B34;
    __vtbl__Q2_2ui21Control_WifiCmnButton = 0x100D5A2C;

    /* ui::Control_CourseButton */
    __ct__Q2_2ui20Control_CourseButtonFb = 0x0257D8C4;


    /* ui::Control_CupButton */
    __ct__Q2_2ui17Control_CupButtonFb = 0x0257CDF8;


    /* ui::UIPage */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui6UIPageSFv = 0x101AB210;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui6UIPageSFv = 0x101B24E4;
    createControl___Q2_2ui6UIPageFPQ2_2ui9UIControlT1RCQ2_4sead23SafeStringBase__tm__2_c = 0x0253E970;
    pushInput__Q2_2ui6UIPageFRQ2_2ui7UIInput = 0x0253F460;
    loadControl___Q2_2ui6UIPageFPQ2_2ui9UIControliRCQ2_4sead23SafeStringBase__tm__2_c = 0x0253E8C8;
    createAnimator__Q2_2ui6UIPageFiPQ2_2ui9UIControlT1 = 0x0253EA24;
    toExit__Q2_2ui6UIPageFv = 0x0253EC28;
    toIn__Q2_2ui6UIPageFPQ2_2ui6UIFlow = 0x0253EFB4;

    /* ui::UIAnimator */
    bind__Q2_2ui10UIAnimatorFiRCQ2_4sead23SafeStringBase__tm__2_c = 0x025307DC;
    stop__Q2_2ui10UIAnimatorFif = 0x02530B5C;
    play___Q2_2ui10UIAnimatorFi = 0x0253098C;
    isEnd__Q2_2ui10UIAnimatorCFi = 0x02530FCC;
    setSpeed__Q2_2ui10UIAnimatorFifb = 0x025309F4;

    /* ui::Page_CourseBase */
    LoadPanes__Q2_2ui15Page_CourseBaseFPQ2_2ui9UIControlb = 0x025B9680;
    LoadAnimations__Q2_2ui15Page_CourseBaseFPQ2_2ui9UIControl = 0x025B94B4;
    initialize__Q2_2ui15Page_CourseBaseFv = 0x025B9B44;
    onCalc__Q2_2ui15Page_CourseBaseFv = 0x025BAC38;

    /* ui::Page_CourseGP */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui13Page_CourseGP = 0x101B29AC;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui13Page_CourseGP = 0x101B2F24;
    onHandler__Q2_2ui13Page_CourseGPFRQ2_2ui7UIEvent = 0x025BBD18;

    /* ui::Page_CourseVS */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui13Page_CourseVS = 0x101B29AC;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui13Page_CourseVS = 0x101B2F24;
    onHandler__Q2_2ui13Page_CourseVSFRQ2_2ui7UIEvent = 0x025BC24C;
    toOut__Q2_2ui13Page_CourseVSFv = 0x025BAF9C;

    /* ui::Page_CourseWiFi */
    onCreate__Q2_2ui15Page_CourseWiFiFv = 0x025FD934;
    onHandler__Q2_2ui15Page_CourseWiFiFRQ2_2ui7UIEvent = 0x025FDCF8;

    /* ui::Page_TitleTop */
    onCreate__Q2_2ui13Page_TitleTopFv = 0x025ED27C;

    /* ui::Page_WifiTop */
    onCreate__Q2_2ui12Page_WifiTopFv = 0x025F3A48;

    /* ui::Page_Race */
    onCreate__Q2_2ui9Page_RaceFv = 0x02640C80;
    loadTimeControl___Q2_2ui9Page_RaceFi = 0x02640B48;
    onCalc__Q2_2ui9Page_RaceFv = 0x02642ABC;
    bindWindowLayout___Q2_2ui9Page_RaceFPQ2_2ui9UIControlPQ2_2ui10RaceWindow = 0x0263FFC8;

    /* ui::Page_Bg */
    onCreate__Q2_2ui7Page_BgFv = 0x025E4780;

    /* ui::UIHeap */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui6UIHeapSFv = 0x101AB20C;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui6UIHeapSFv = 0x101AB520;


    /* ui::UIEngine */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui8UIEngineSFv = 0x101AB53C;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui8UIEngineSFv = 0x101B26E8;
    spInstance__Q2_2ui8UIEngine = 0x1018A16C;
    next__Q2_2ui12UICursorLinkFUii = 0x02538B2C;


    /* ui::UICursor */
    next___Q2_2ui8UICursorFiT1Ui = 0x02537CE0;

    /* ui::UIFlow */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui6UIFlowSFv = 0x101AB204;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui6UIFlowSFv = 0x101B2AF8;

    /* Flow_Reset */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui10Flow_ResetSFv = 0x101B2500;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui10Flow_ResetSFv = 0x101B2BB4;


    /* ui::Flow_Open */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui9Flow_OpenSFv = 0x101B24F8;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui9Flow_OpenSFv = 0x101B2B14;

    /* ui::UISceneFlow */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui11UISceneFlowSFv = 0x101AB208;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui11UISceneFlowSFv = 0x101B2AF4;

    /* ui::Flow_Scene */
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui10Flow_SceneSFv = 0x101B2504;
    typeInfo__L0__getRuntimeTypeInfoStatic__Q2_2ui10Flow_SceneSFv = 0x101B2BB8;

    /* sys::FlagAccessor */
    isOpen__Q2_3sys12FlagAccessorCFQ2_4mush12EGrandPrixID = 0x024D7810;

    /* nn::pia::transport::StationManager */
    s_pInstance__Q4_2nn3pia9transport14StationManager = 0x101A9ABC;

    /* nn::pia::transport::StationProtocol */
    SendDenyingConnectionResponse__Q4_2nn3pia9transport15StationProtocolFRCQ4_2nn3pia6common14StationAddressUc = 0x02A3CC54;
    ParseConnectionRequestCommon__Q4_2nn3pia9transport15StationProtocolFRCQ4_2nn3pia9transport23ReceivedMessageAccessorb = 0x02A3D70C;
    GetConnectionRequestDataSize__Q4_2nn3pia9transport15StationProtocolCFv = 0x02A3B0F8;

    /* nn::pia::transport::StationConnectionInfoTable */
    s_pInstance__Q4_2nn3pia9transport26StationConnectionInfoTable = 0x101A9ACC;

    /* nn::pia::transport::StationConnectionInfo */
    Serialize__Q4_2nn3pia9transport21StationConnectionInfoCFPUcPUiUi = 0x02A3ACF8;

    /* object:: */
    IsRaceState__6objectFv = 0x0244171C;

    /* object::ObjectEngineCollection */
    spRaceDirector__Q2_6object22ObjectEngineCollection = 0x1018850C;
    spKartDirector__Q2_6object22ObjectEngineCollection = 0x10188518;

    /* object::KartDirector */
    getKartUnit__Q2_6object12KartDirectorFi = 0x0218FAC0;

    /* object::MapObjParameter */
    initialize__Q2_6object15MapObjParameterFv = 0x0233BEDC;
    __ct__Q3_6object15MapObjParameter9ParameterFRCQ2_2al9ByamlIter = 0x0233BCC4;

    /* sys::ResourceLoader */
    __CPR104__loadDirect__Q2_3sys14ResourceLoaderFRCQ2_4sead23SafeStringBase__tm__2_cRCQ3_3sysJ19J7LoadArg = 0x024E8FB0;

    /* al::ByamlIter */
    __ct__Q2_2al9ByamlIterFv = 0x0266A1B8;
    __ct__Q2_2al9ByamlIterFPCUc = 0x0266A1F8;
    getSize__Q2_2al9ByamlIterCFv = 0x0266AEE8;
    __ct__Q2_2al9ByamlIterFRCQ2_2al9ByamlIter = 0x0266A298;
    tryGetIterByIndex__Q2_2al9ByamlIterCFPQ2_2al9ByamlIteri = 0x0266AB58;
 
}