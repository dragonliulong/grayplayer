#include "GrayPlayer.h"
#include <QCoreApplication>
#include <QSettings>
#include "MultimediaDecodeSetting.h"

void GrayPlayer::readDecodeSetting()
{
    QString path = QCoreApplication::applicationDirPath() + "/decodeSetting.ini";
    QSettings setting(path, QSettings::IniFormat);

    if(setting.value("launch/first", true).toBool())
        resetDecodeSetting();

    decodeMode = (DecodeMode)setting.value("decode/decodeMode", decodeModeDef).toInt();
    sw_thread_count = setting.value("software/sw_thread_count", sw_thread_count_def).toInt();
    adapter_choice = setting.value("d3d11va/adapter_choice", adapter_choice_def).toInt();
    swap_chain_count = setting.value("d3d11va/swap_chain_count", swap_chain_count_def).toInt();

    for(int i=0; i<5; i++)
    {
        if(dxgi_format_def == dxgi_formats[i])
        {
            dxgi_format = dxgi_formats[setting.value("d3d11va/dxgi_format", i).toInt()];
            break;
        }
    }

    for(int i=0; i<4; i++)
    {
        if(dxgi_swap_effect_def == dxgi_swap_effects[i])
        {
            dxgi_swap_effect = dxgi_swap_effects[setting.value("d3d11va/dxgi_swap_effect", i).toInt()];
            break;
        }
    }

    flipex_mode = setting.value("dxva2/flipex_mode", flipex_mode_def).toBool();

    //设置渲染模式
    if(decodeMode == SOFTWARE || decodeMode == DXVA2) renderMode = D3D9;
    else renderMode = D3D11;
}

void GrayPlayer::resetDecodeSetting()
{
    QString path = QCoreApplication::applicationDirPath() + "/decodeSetting.ini";
    QSettings setting(path, QSettings::IniFormat);

    setting.setValue("launch/first", false);

    //--------------------------------------------------------------

    setting.setValue("decode/decodeMode", decodeModeDef);
    setting.setValue("software/sw_thread_count", sw_thread_count_def);
    setting.setValue("d3d11va/adapter_choice", adapter_choice_def);
    setting.setValue("d3d11va/swap_chain_count", swap_chain_count_def);

    for(int i=0; i<5; i++)
    {
        if(dxgi_format_def == dxgi_formats[i])
        {
            setting.setValue("d3d11va/dxgi_format", i);
            break;
        }
    }

    for(int i=0; i<4; i++)
    {
        if(dxgi_swap_effect_def == dxgi_swap_effects[i])
        {
            setting.setValue("d3d11va/dxgi_swap_effect", i);
            break;
        }
    }

    setting.setValue("dxva2/flipex_mode", flipex_mode_def);

    //--------------------------------------------------------------
}
