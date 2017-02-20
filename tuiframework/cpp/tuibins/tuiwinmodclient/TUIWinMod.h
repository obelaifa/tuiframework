
#include <tuiframework/client/client.h>
#include <tuitypes/common/CommonTypeReg.h>


class TUIWinMod
{
public:
	TUIWinMod(void);
	virtual ~TUIWinMod(void);

	//// Connecting Signals and Slots
	void connect();
    void disconnect();
	void AnalogSignalChanged(const PackedAnalogEvent * e);
	//void MatrixSignalChanged(const PackedMatrix4Event * e);
	//void Matrix1SignalChanged(const Matrix4Event * e);

	void DigitalSignalChanged(const PackedIntegerEvent * e);
	void WordSignalChanged(const PackedWORDEvent *e);
	void dWordSignalChanged(const PackedDWORDEvent *e);

private:
	PackedType<int> byteValues;
	PackedType<float> floatValues;
	PackedType<WORD> wordValues;
	PackedType<DWORD> dWordValues;

	tuiframework::IEventChannel * dOutChannel;
	tuiframework::IEventChannel * aOutChannel;
	tuiframework::IEventChannel * wOutChannel;
	tuiframework::IEventChannel * dwOutChannel;
};

