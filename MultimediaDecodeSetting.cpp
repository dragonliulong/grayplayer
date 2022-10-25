#include "MultimediaDecodeSetting.h"

//-----------------------------------------------------------

vector<IDXGIAdapter*> adapters;
const int adapter_count = VideoD3D11::enumAdapters();

const DXGI_FORMAT dxgi_formats[5]=
{
    DXGI_FORMAT_B8G8R8A8_UNORM,       //默认
    DXGI_FORMAT_R8G8B8A8_UNORM,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,  //颜色较淡
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,  //颜色较淡
    DXGI_FORMAT_R10G10B10A2_UNORM
};

const DXGI_SWAP_EFFECT dxgi_swap_effects[4]=
{
    DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
    DXGI_SWAP_EFFECT_SEQUENTIAL,
    DXGI_SWAP_EFFECT_FLIP_DISCARD,
    DXGI_SWAP_EFFECT_DISCARD          //默认
};

//-----------------------------------------------------------

//------------------------------默认设置---------------------------------

const DecodeMode decodeModeDef = D3D11VA;  //默认D3D11VA硬解
const RenderMode renderModeDef = D3D11;  //默认D3D11渲染

const int sw_thread_count_def = 3;  //默认软解线程数3

const bool flipex_mode_def = false; //默认关闭D3D9 flipex模式

//以下为D3D11VA解码默认设置
const int adapter_choice_def = 0;  //默认显卡解码
const DXGI_FORMAT dxgi_format_def = DXGI_FORMAT_B8G8R8A8_UNORM;  //默认显示格式
const int swap_chain_count_def = 1;  //默认交换链个数1
const DXGI_SWAP_EFFECT dxgi_swap_effect_def = DXGI_SWAP_EFFECT_DISCARD;  //默认交换效果

//----------------------------------------------------------------------

DecodeMode decodeMode = decodeModeDef;
RenderMode renderMode = renderModeDef;

int sw_thread_count = sw_thread_count_def;
bool flipex_mode = flipex_mode_def;
int adapter_choice = adapter_choice_def;
DXGI_FORMAT dxgi_format = dxgi_format_def;
int swap_chain_count = swap_chain_count_def;
DXGI_SWAP_EFFECT dxgi_swap_effect = dxgi_swap_effect_def;
