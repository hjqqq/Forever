#include "CNPC.h"

CNPC::CNPC(std::string machineName, int kindID, long long uid, float fx, float fy):
CUnitObject(machineName, NPC_INFO::getInfo(kindID)->getName(), uid, 50)
{
	if(create(kindID))
	{
		setPosition(fx, fy);
      setTargetPosition(fx, fy);
		BasicAttribute basAttr;
		//memset(&basAttr, 1000, sizeof(basAttr));
		basAttr.iAGI = 1000;
		basAttr.iDEX = 1000;
		basAttr.iINT = 1000;
		basAttr.iSTR = 1000;
		basAttr.iVIT = 1000;
		basAttr.iWIL = 1000;
		setBasAttr(basAttr);

		std::string actionFile = NPC_INFO::getInfo(kindID)->getActionSystemFile();
      if(m_actionSystem.read("../" + actionFile) == false)
         m_actionSystem.read(actionFile);
	}
}

void CNPC::initNPC()
{
	if(NPC_INFO::read("NPC.fla"))
	{
	}
	else
	{
		CNPCInfo* pnpc = new CNPCInfo();
		std::vector<std::string> talk;
		std::string str;
		str = "hello!";
		talk.push_back(str);
		str.clear();
		str = "�ڬO����";
		talk.push_back(str);
		str.clear();
		str = "�A�n!";
		talk.push_back(str);
		str.clear();
		std::vector<int> quest;
		std::vector<int> sell;
		pnpc->initNPCInfo("����", "ShugoFemale.mesh", "ShugoFemale.acs", talk, VILLAGER, quest, sell);
		addInfo(pnpc);

		pnpc = new CNPCInfo();
		talk.clear();
		str.clear();
		str = "���F��n���ڶ�?";
		talk.push_back(str);
		str.clear();
		str = "���s�F���!";
		talk.push_back(str);
		str.clear();
		str = "�R�I�F��a!";
		talk.push_back(str);
		str.clear();
		quest.clear();
		sell.clear();
		sell.push_back(39);
		sell.push_back(40);
		sell.push_back(41);
		sell.push_back(42);
		sell.push_back(43);
		sell.push_back(44);
		sell.push_back(45);
		sell.push_back(46);
		sell.push_back(47);
		pnpc->initNPCInfo("�ޯ���", "ShugoMale.mesh", "ShugoMale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);
		
		pnpc = new CNPCInfo();
		talk.clear();
		str.clear();
		str = "���F��n���ڶ�?";
		talk.push_back(str);
		str.clear();
		str = "�ոճo�~�Ĥ��a!";
		talk.push_back(str);
		str.clear();
		str = "�R�I�F��a!";
		talk.push_back(str);
		str.clear();
		quest.clear();
		sell.clear();
		sell.push_back(37);
		sell.push_back(38);
		pnpc->initNPCInfo("�Ĥ����", "ShugoFemale.mesh", "ShugoFemale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);

		pnpc = new CNPCInfo();
		talk.clear();
		str.clear();
		str = "���F��n���ڶ�?";
		talk.push_back(str);
		str.clear();
		str = "�ոզu�îM�˧a!";
		talk.push_back(str);
		str.clear();
		str = "�ݭn�����?";
		talk.push_back(str);
		str.clear();
		quest.clear();
		sell.clear();
		sell.push_back(3);
		sell.push_back(4);
		sell.push_back(5);
		sell.push_back(6);
		sell.push_back(27);
		sell.push_back(32);
		pnpc->initNPCInfo("�u�îM�˦��", "ShugoMale.mesh", "ShugoMale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);

		pnpc = new CNPCInfo();
		talk.clear();
		str.clear();
		str = "���F��n���ڶ�?";
		talk.push_back(str);
		str.clear();
		str = "�ոսլd�ήM�˧a!";
		talk.push_back(str);
		str.clear();
		str = "�R�I�F��a!";
		talk.push_back(str);
		str.clear();
		quest.clear();
		sell.clear();
		sell.push_back(7);
		sell.push_back(8);
		sell.push_back(9);
		sell.push_back(10);
		sell.push_back(11);
		sell.push_back(28);
		sell.push_back(33);
		pnpc->initNPCInfo("�լd�ήM�˦��", "ShugoFemale.mesh", "ShugoFemale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);

		pnpc = new CNPCInfo();
		talk.clear();
		str.clear();
		str = "���F��n���ڶ�?";
		talk.push_back(str);
		str.clear();
		str = "�ոիi��M�˧a!";
		talk.push_back(str);
		str.clear();
		str = "�ݭn�����?";
		talk.push_back(str);
		str.clear();
		quest.clear();
		sell.clear();
		sell.push_back(12);
		sell.push_back(13);
		sell.push_back(14);
		sell.push_back(15);
		sell.push_back(16);
		sell.push_back(29);
		sell.push_back(34);
		pnpc->initNPCInfo("�i��M�˦��", "ShugoMale.mesh", "ShugoMale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);

		pnpc = new CNPCInfo();
		talk.clear();
		str.clear();
		str = "���F��n���ڶ�?";
		talk.push_back(str);
		str.clear();
		str = "�ոզu�øU�Ҫ��M�˧a!";
		talk.push_back(str);
		str.clear();
		str = "�ݭn�����?";
		talk.push_back(str);
		str.clear();
		quest.clear();
		sell.clear();
		sell.push_back(17);
		sell.push_back(18);
		sell.push_back(19);
		sell.push_back(20);
		sell.push_back(21);
		sell.push_back(30);
		sell.push_back(35);
		pnpc->initNPCInfo("�u�øU�Ҫ��M�˦��", "ShugoMale.mesh", "ShugoMale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);

		pnpc = new CNPCInfo();
		talk.clear();
		str.clear();
		str = "���F��n���ڶ�?";
		talk.push_back(str);
		str.clear();
		str = "�ոռ��㪺���ԯǴ��M�˧a!";
		talk.push_back(str);
		str.clear();
		str = "�R�I�F��a!";
		talk.push_back(str);
		str.clear();
		quest.clear();
		sell.clear();
		sell.push_back(22);
		sell.push_back(23);
		sell.push_back(24);
		sell.push_back(25);
		sell.push_back(26);
		sell.push_back(31);
		sell.push_back(36);
		pnpc->initNPCInfo("���㪺���ԯǴ����", "ShugoFemale.mesh", "ShugoFemale.acs", talk, STORE, quest, sell);
		addInfo(pnpc);
	}
}

CNPC::~CNPC()
{
}

bool CNPC::create(unsigned int kindID)
{
	if(false == NPC_INFO::checkID(kindID))
    {
        return false;
    }
    NPC_INFO::create(kindID);
    CNPCInfo* pInfo = getInfo();
    if(NULL != pInfo)
    {
        return true;
    }
    return false;
}

#ifdef _GAMEENGINE_2D_
void CNPC::draw(HDC hdc)
{
	CUnitObject::draw(hdc);
	//����
	int size = 20;
   char buf[128];
   memset(buf, 0, sizeof(buf));
   sprintf_s(buf, sizeof(buf), "%s", getName().c_str());
   TextOut(hdc, (int)getPosition().fX - size, (int)getPosition().fY + size + 5, buf, strlen(buf));
}
#endif