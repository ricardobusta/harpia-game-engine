package busta.quest.character;

import busta.quest.skill.Skill;

public class Character {
	int hp;
	int mp;
	
	int atk;
	int def;
	int mag;
	
	Skill[] skill = new Skill[4];
	
	public int getHp() {
		return hp;
	}
	public void setHp(int hp) {
		this.hp = hp;
	}
	public int getMp() {
		return mp;
	}
	public void setMp(int mp) {
		this.mp = mp;
	}
	public int getAtk() {
		return atk;
	}
	public void setAtk(int atk) {
		this.atk = atk;
	}
	public int getDef() {
		return def;
	}
	public void setDef(int def) {
		this.def = def;
	}
	public int getMag() {
		return mag;
	}
	public void setMag(int mag) {
		this.mag = mag;
	}
}
