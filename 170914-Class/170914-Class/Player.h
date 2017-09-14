#pragma once

enum EP_STATE
{
    EP_IDLE, EP_WALK, EP_RUN, EP_ATTACK
};

class Player
{
private:
    EP_STATE m_epState;
	string m_strName;
	int m_hp;
	int m_mp;
	int m_atk;
	int m_def;

protected:


public:
	Player();
	~Player();

	string GetName() {
		return m_strName;
	}


    //  GET, SET
	int GetHp() {
		return m_hp;
	}
	void SetHp(int hp) {
		m_hp = hp;
	}

    int GetMp() {
        return m_mp;
    }
    void SetMp(int mp) {
        m_mp = mp;
    }

    int GetAtk() {
        return m_atk;
    }

    int GetDef() {
        return m_def;
    }


    //  BE HAVIOR
	void GetDamage(int Dmg);
    void Idle();    //  EP_IDLE
    void Walk();    //  EP_WALK
    void Run();     //  EP_RUN
    void Attack();  //  EP_ATTACK
};