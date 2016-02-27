#pragma once

#include "EffectHandler.h"



class AdalightEffect : public EffectHandler
{

public:
	AdalightEffect(HardwareSerial & Serial, int defaultSpeed) : _Serial(Serial), _defaultSpeed(defaultSpeed), _vars(nullptr) {};

	bool Start() override;
	bool Stop() override;
	void Refresh() override
	{
		Start();
	}
	bool Run() override;

	//  InitVars is overridden from PropertyManager.  delete is called automagically on all vars created with addVar.
	bool InitVars() override
	{
		_vars = new AdalightEffectVars; 
		addVar(new Variable<int>("serialspeed"));
//		setVar<int>("serialspeed", _defaultSpeed);
	}

	int serialspeed()  {  return getVar<int>("serialspeed"); }

	static void Adalight_Flash();

private:
	HardwareSerial & _Serial;
	int _defaultSpeed;
	enum mode {MODE_HEADER = 0, MODE_CHECKSUM, MODE_DATA, MODE_SHOW, MODE_FINISH};

	struct AdalightEffectVars {
		uint16_t effectbuf_position{0};
		mode state{MODE_HEADER};
		int effect_timeout{0};
		uint8_t prefixcount{0};
		unsigned long ada_sent{0}; 
		unsigned long pixellatchtime{0};
	};

	AdalightEffectVars * _vars; 
	const unsigned long serialTimeout = 15000;

};