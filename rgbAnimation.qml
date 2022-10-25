import QtQuick 2.15
import QtQuick.Window 2.15

Rectangle
{
    width: parent ? parent.width : 0
    height: parent ? parent.height : 0
    radius: 200
    visible: true

    property var rs: [1,1,0,0,0,1,1]
    property var gs: [0,1,1,1,0,0,0]
    property var bs: [0,0,0,1,1,1,0]

    property var finishInterval: 1200  //1200 ms 一次变色完成
    property var checkInterval: 12   //12 ms 一次检测

    function changeColor(i, progress)
    {
        var j = (i+1)%7;
        var r = rs[i] + (rs[j]-rs[i])*progress;
        var g = gs[i] + (gs[j]-gs[i])*progress;
        var b = bs[i] + (bs[j]-bs[i])*progress;
        color = Qt.rgba(r,g,b,1);
    }

    Timer
    {
        interval: checkInterval
        running: true
        repeat: true
        property int i: 0
        property int past: 0

        onTriggered:
        {
            changeColor(i, past/finishInterval);
            past = (past+checkInterval)%finishInterval;
            if(past==0) i=(i+1)%7;   
        }
    }
}
