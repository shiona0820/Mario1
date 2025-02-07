#pragma once

#include "../Develop/Objects/GameObject.h"

class Hatena : public GameObject
{
public:
	Hatena();
	~Hatena();
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;
};

