#include "TUIWinMod.h"

using namespace tuiframework;
using namespace std;

TUIWinMod::TUIWinMod(void)
{

}


TUIWinMod::~TUIWinMod(void)
{
}



void TUIWinMod::connect() {
	
    try {
		CONNECT(PackedAnalogEvent, "WinModTUIApp", "fIn", TUIWinMod, this, &TUIWinMod::AnalogSignalChanged);
		CONNECT(PackedIntegerEvent, "WinModTUIApp", "bIn", TUIWinMod, this, &TUIWinMod::DigitalSignalChanged);
		CONNECT(PackedWORDEvent, "WinModTUIApp", "wIn", TUIWinMod, this, &TUIWinMod::WordSignalChanged);
		CONNECT(PackedDWORDEvent, "WinModTUIApp", "dwIn", TUIWinMod, this, &TUIWinMod::dWordSignalChanged);	

		// Output Sink
		
		this->dOutChannel = getSinkChannel("WinModTUIApp", "bOut");
        if (this->dOutChannel == 0) {
            cout << "this->dOutChannel == 0" << endl;
        }

		this->aOutChannel = getSinkChannel("WinModTUIApp", "fOut");
        if (this->aOutChannel == 0) {
            cout << "this->aOutChannel == 0" << endl;
        }
		
		this->wOutChannel = getSinkChannel("WinModTUIApp", "wOut");
        if (this->wOutChannel == 0) {
            cout << "this->wOutChannel == 0" << endl;
        }
		
		this->dwOutChannel = getSinkChannel("WinModTUIApp", "dwOut");
        if (this->dwOutChannel == 0) {
            cout << "this->DwOutChannel == 0" << endl;
        }
		

    } catch (const Exception & e) {
        cerr << "Exception" << endl;
        cerr << e.getFormattedString() << endl;
    }
	
}


void TUIWinMod::disconnect() {
    try 
	{
		DISCONNECT(PackedAnalogEvent, "WinModTUIApp", "fIn", TUIWinMod, this, &TUIWinMod::AnalogSignalChanged);
		DISCONNECT(PackedIntegerEvent, "WinModTUIApp", "bIn", TUIWinMod, this, &TUIWinMod::DigitalSignalChanged);
		DISCONNECT(PackedWORDEvent, "WinModTUIApp", "wIn", TUIWinMod, this, &TUIWinMod::WordSignalChanged);
		DISCONNECT(PackedDWORDEvent, "WinModTUIApp", "dwIn", TUIWinMod, this, &TUIWinMod::dWordSignalChanged);

    } catch (const Exception & e) 
	{
        cerr << "Exception" << endl;
        cerr << e.getFormattedString() << endl;
    }
}


void TUIWinMod::WordSignalChanged(const PackedWORDEvent *e)
{
	
	this->wordValues = e->getPayload();
	PackedWORDEvent *wordChangeEvent = new PackedWORDEvent(-1,-1,wordValues);
	this->wOutChannel->push(wordChangeEvent);
}


void TUIWinMod::dWordSignalChanged(const PackedDWORDEvent *e)
{
	this->dWordValues = e->getPayload();
	PackedDWORDEvent *dWordChangeEvent = new PackedDWORDEvent(-1,-1,dWordValues);
	this->dwOutChannel->push(dWordChangeEvent);
}



void TUIWinMod::AnalogSignalChanged(const PackedAnalogEvent * e) {
	
	this->floatValues = e->getPayload();
	
	/*
	for(int i = 0; i < e->getPayload().size(); i++)
	{
		cout << "value:" << i << " " << e->getPayload().getData().at(i) << endl;
	}
	*/
	//AnalogVectorChangedEvent* analogChangeEvent = new AnalogVectorChangedEvent(-1, -1, floatValues);
	//this->aOutChannel->push(analogChangeEvent);
	
	//delete analogChangeEvent;
	//delete e;
}

/*
void TUIWinMod::MatrixSignalChanged(const PackedMatrix4Event * e) {

	//cout << "Test" << endl;
	//cout << e->getPayload().getFloats().getData().size()<< endl; 
	cout << "matrix: " << e->getPayload()<< endl;
	//cout << e->getPayload().getData().second << endl;
	//cout << "Size: "<< this->floatValues.size() << endl;
	//cout << "Size: "<< floatValue.size() << endl;


	//cout << floatValues.getData()[0] << endl;
	//AnalogVectorChangedEvent* analogChangeEvent = new AnalogVectorChangedEvent(-1, -1, floatValues);
	//this->aOutChannel->push(analogChangeEvent);

	//delete analogChangeEvent;
	//delete e;
}
*/
/*
void TUIWinMod::Matrix1SignalChanged(const Matrix4Event * e) {

	//cout << "Test" << endl;
	//cout << e->getPayload().getFloats().getData().size()<< endl; 
	cout << "matrix: " << e->getPayload() << endl;
	//cout << e->getPayload().getData().second << endl;
	//cout << "Size: "<< this->floatValues.size() << endl;
	//cout << "Size: "<< floatValue.size() << endl;
	//
	//for(int i=0;i<floatValues.size();i++)
	//{
	//cout << "Analog Signal: " << floatValues.at(i) << endl;
	//}
	//

	//cout << floatValues.getData()[0] << endl;
	//AnalogVectorChangedEvent* analogChangeEvent = new AnalogVectorChangedEvent(-1, -1, floatValues);
	//this->aOutChannel->push(analogChangeEvent);

	//delete analogChangeEvent;
	//delete e;
}
*/

void TUIWinMod::DigitalSignalChanged(const PackedIntegerEvent * e) {
	//this->byteValues = e->getPayload();
	
	
	//Integer View for Debug

	//for(int i=0;i<byteValues.size();i++)
	//{
	//	cout << "Byte Signal: " << (byteValues.at(i)) << endl;
	//}
	
	// Hex View for Debug
	//cout <<"Hex: " << hex << e->getPayload() << endl;
	

	//IntegerVectorChangedEvent* byteChangeEvent = new IntegerVectorChangedEvent(-1, -1, byteValues);
	//this->dOutChannel->push(byteChangeEvent);

	//delete byteChangeEvent;
	//delete e;
}
