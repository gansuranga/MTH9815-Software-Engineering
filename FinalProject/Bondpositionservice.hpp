#pragma once
/**
 * Bondpositionservice.hpp
 * Define the BondpositionserviceListener, BondPositionService class
 * @Create by Xinlu Xiao
 */
#ifndef BONDPOSITIONSERVICE_HPP
#define BONDPOSITIONSERVICE_HPP

#include <iostream>
#include <string>
#include <map>
#include "globalfunctions.hpp"
#include "positionservice.hpp"
#include "Bondriskservice.hpp"
#include "soa.hpp"

using namespace std;

class BondpositionserviceListener : public ServiceListener<Position<Bond>>
{
public:
	// Add data to the RiskService
	virtual void ProcessAdd(Position<Bond> &data) override
	{
		bond_service->AddPosition(data);
	}

	// Listener callback to process a remove event to the Service
	virtual void ProcessRemove(Position<Bond> &data) override {};

	// Listener callback to process an update event to the Service
	virtual void ProcessUpdate(Position<Bond> &data) override {};

	// Add instance
	static BondpositionserviceListener* Add_example()
	{
		static BondpositionserviceListener example;
		return &example;
	}

private:
	// ctor of BondpositionserviceListener
	BondpositionserviceListener()
	{
		bond_service = BondRiskService::Add_example();
	}

	BondRiskService *bond_service = nullptr;
	
};

class BondPositionService : public Service<string, Position<Bond>>
{
public:
	// Get data on our service given a key
	//virtual Position<Bond>& GetData(string key) override {};

	// The callback that a Connector should invoke for any new or updated data
	virtual void OnMessage(Position<Bond> &data) override
	{
		for each(auto listener_instance in bond_listeners)
		{
			listener_instance->ProcessAdd(data);
		}
	}

	// Add instance
	static BondPositionService* Add_example()
	{
		static BondPositionService example;
		return &example;
	}

private:
	BondPositionService()
	{
		AddListener(*(BondpositionserviceListener::Add_example()));
	}

};

#endif
