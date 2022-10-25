/****************************************************************************
** Meta object code from reading C++ file 'MultimediaMain.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../MultimediaMain.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultimediaMain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MultimediaEntry_t {
    QByteArrayData data[16];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MultimediaEntry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MultimediaEntry_t qt_meta_stringdata_MultimediaEntry = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MultimediaEntry"
QT_MOC_LITERAL(1, 16, 8), // "openFail"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "totalTimeChange"
QT_MOC_LITERAL(4, 42, 16), // "callAudioDecoder"
QT_MOC_LITERAL(5, 59, 16), // "callVideoDecoder"
QT_MOC_LITERAL(6, 76, 15), // "callAudioPlayer"
QT_MOC_LITERAL(7, 92, 15), // "callVideoPlayer"
QT_MOC_LITERAL(8, 108, 22), // "callVideoDecoderPlayer"
QT_MOC_LITERAL(9, 131, 4), // "open"
QT_MOC_LITERAL(10, 136, 5), // "char*"
QT_MOC_LITERAL(11, 142, 4), // "file"
QT_MOC_LITERAL(12, 147, 11), // "sliderPress"
QT_MOC_LITERAL(13, 159, 13), // "sliderRelease"
QT_MOC_LITERAL(14, 173, 4), // "skip"
QT_MOC_LITERAL(15, 178, 11) // "can_give_up"

    },
    "MultimediaEntry\0openFail\0\0totalTimeChange\0"
    "callAudioDecoder\0callVideoDecoder\0"
    "callAudioPlayer\0callVideoPlayer\0"
    "callVideoDecoderPlayer\0open\0char*\0"
    "file\0sliderPress\0sliderRelease\0skip\0"
    "can_give_up"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MultimediaEntry[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       4,    0,   78,    2, 0x06 /* Public */,
       5,    0,   79,    2, 0x06 /* Public */,
       6,    0,   80,    2, 0x06 /* Public */,
       7,    0,   81,    2, 0x06 /* Public */,
       8,    0,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   83,    2, 0x0a /* Public */,
      12,    0,   86,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,
      14,    2,   88,    2, 0x0a /* Public */,
      14,    1,   93,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Bool,    2,   15,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void MultimediaEntry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MultimediaEntry *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFail(); break;
        case 1: _t->totalTimeChange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->callAudioDecoder(); break;
        case 3: _t->callVideoDecoder(); break;
        case 4: _t->callAudioPlayer(); break;
        case 5: _t->callVideoPlayer(); break;
        case 6: _t->callVideoDecoderPlayer(); break;
        case 7: _t->open((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 8: _t->sliderPress(); break;
        case 9: _t->sliderRelease(); break;
        case 10: _t->skip((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->skip((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MultimediaEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultimediaEntry::openFail)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MultimediaEntry::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultimediaEntry::totalTimeChange)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MultimediaEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultimediaEntry::callAudioDecoder)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MultimediaEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultimediaEntry::callVideoDecoder)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MultimediaEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultimediaEntry::callAudioPlayer)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MultimediaEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultimediaEntry::callVideoPlayer)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MultimediaEntry::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultimediaEntry::callVideoDecoderPlayer)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MultimediaEntry::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MultimediaEntry.data,
    qt_meta_data_MultimediaEntry,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MultimediaEntry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultimediaEntry::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MultimediaEntry.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MultimediaEntry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MultimediaEntry::openFail()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MultimediaEntry::totalTimeChange(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MultimediaEntry::callAudioDecoder()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MultimediaEntry::callVideoDecoder()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MultimediaEntry::callAudioPlayer()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MultimediaEntry::callVideoPlayer()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MultimediaEntry::callVideoDecoderPlayer()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
struct qt_meta_stringdata_AudioDecoder_t {
    QByteArrayData data[5];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioDecoder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioDecoder_t qt_meta_stringdata_AudioDecoder = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AudioDecoder"
QT_MOC_LITERAL(1, 13, 11), // "startDecode"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "init"
QT_MOC_LITERAL(4, 31, 6) // "decode"

    },
    "AudioDecoder\0startDecode\0\0init\0decode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioDecoder[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AudioDecoder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioDecoder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startDecode(); break;
        case 1: _t->init(); break;
        case 2: _t->decode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AudioDecoder::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioDecoder::startDecode)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AudioDecoder::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AudioDecoder.data,
    qt_meta_data_AudioDecoder,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AudioDecoder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioDecoder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioDecoder.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AudioDecoder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AudioDecoder::startDecode()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_VideoDecoder_t {
    QByteArrayData data[5];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoDecoder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoDecoder_t qt_meta_stringdata_VideoDecoder = {
    {
QT_MOC_LITERAL(0, 0, 12), // "VideoDecoder"
QT_MOC_LITERAL(1, 13, 11), // "startDecode"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "init"
QT_MOC_LITERAL(4, 31, 6) // "decode"

    },
    "VideoDecoder\0startDecode\0\0init\0decode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoDecoder[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoDecoder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoDecoder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startDecode(); break;
        case 1: _t->init(); break;
        case 2: _t->decode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoDecoder::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoDecoder::startDecode)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VideoDecoder::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_VideoDecoder.data,
    qt_meta_data_VideoDecoder,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoDecoder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoDecoder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoDecoder.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VideoDecoder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void VideoDecoder::startDecode()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_AudioPlayer_t {
    QByteArrayData data[7];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AudioPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AudioPlayer_t qt_meta_stringdata_AudioPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AudioPlayer"
QT_MOC_LITERAL(1, 12, 9), // "startPlay"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 19), // "proSliderTimerStart"
QT_MOC_LITERAL(4, 43, 18), // "proSliderTimerStop"
QT_MOC_LITERAL(5, 62, 4), // "init"
QT_MOC_LITERAL(6, 67, 4) // "play"

    },
    "AudioPlayer\0startPlay\0\0proSliderTimerStart\0"
    "proSliderTimerStop\0init\0play"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AudioPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startPlay(); break;
        case 1: _t->proSliderTimerStart(); break;
        case 2: _t->proSliderTimerStop(); break;
        case 3: _t->init(); break;
        case 4: _t->play(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::startPlay)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::proSliderTimerStart)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AudioPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioPlayer::proSliderTimerStop)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AudioPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AudioPlayer.data,
    qt_meta_data_AudioPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AudioPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioPlayer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AudioPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AudioPlayer::startPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AudioPlayer::proSliderTimerStart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AudioPlayer::proSliderTimerStop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_VideoPlayer_t {
    QByteArrayData data[7];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPlayer_t qt_meta_stringdata_VideoPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoPlayer"
QT_MOC_LITERAL(1, 12, 9), // "startPlay"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "timerStart"
QT_MOC_LITERAL(4, 34, 4), // "init"
QT_MOC_LITERAL(5, 39, 4), // "play"
QT_MOC_LITERAL(6, 44, 4) // "sync"

    },
    "VideoPlayer\0startPlay\0\0timerStart\0"
    "init\0play\0sync"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPlayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   43,    2, 0x0a /* Public */,
       5,    0,   44,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startPlay(); break;
        case 1: _t->timerStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->init(); break;
        case 3: _t->play(); break;
        case 4: _t->sync(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoPlayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPlayer::startPlay)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VideoPlayer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoPlayer::timerStart)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoPlayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_VideoPlayer.data,
    qt_meta_data_VideoPlayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlayer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VideoPlayer::startPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VideoPlayer::timerStart(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
