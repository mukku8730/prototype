#include "JanpaiManager.h"
#include "Janpai.h"
#include "DebugFont.h"
#include <tchar.h>
#include <cassert>
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

const int JanpaiManager::m_mahjongTilesNum = 136;
static const int START_YAMA_NUM = 34;


/**
	ƒRƒ“ƒXƒgƒ‰ƒNƒ^
*/
JanpaiManager::JanpaiManager() :
m_janpai(new Janpai()) {
	assert(m_janpai != NULL);
}


/**
	ƒfƒXƒgƒ‰ƒNƒ^
*/
JanpaiManager::~JanpaiManager() {
	SAFE_DELETE(m_janpai);
}


/**
	XVˆ—
*/
void JanpaiManager::Update() {
	for (int i = 0; i < m_mahjongTilesNum; ++i) {
		m_janpai->Update();
	}
}


/**
	è”v‚ğ•`‰æ
	@param tehai	•\¦‚·‚éè”v
*/
void JanpaiManager::DrawTehai(std::vector<std::multiset<HaiType>> tehai) {
	Vector3 southPos = Vector3(-15.0f, 1.2f, -28.0f);
	Vector3 westPos = Vector3(-28.0f, 1.2f, 15.0f);
	Vector3 northPos = Vector3(15.0f, 1.2f, 28.0f);
	Vector3 eastPos = Vector3(28.0f, 1.2f, -15.0f);

	int dirType = DirectionType_South;
	std::vector<std::multiset<HaiType>>::const_iterator playerIt;
	std::multiset<HaiType>::iterator multiIt;
	for (playerIt = tehai.begin(); playerIt != tehai.end(); playerIt++) {
		for (multiIt = playerIt->begin(); multiIt != playerIt->end(); multiIt++) {
			switch (dirType) {
			case DirectionType_South:
				m_janpai->SetPosition(southPos);
				southPos.x += 1.9f;
				m_janpai->SetRotation(Vector3(90.0f, 0.0f, 0.0f));
				break;

			case DirectionType_East:
				m_janpai->SetPosition(eastPos);
				eastPos.z += 1.9f;
				m_janpai->SetRotation(Vector3(-90.0f, -90.0f, 180.0f));
				break;

			case DirectionType_North:
				m_janpai->SetPosition(northPos);
				northPos.x -= 1.9f;
				m_janpai->SetRotation(Vector3(-90.0f, 0.0f, 180.0f));
				break;

			case DirectionType_West:
				m_janpai->SetPosition(westPos);
				westPos.z -= 1.9f;
				m_janpai->SetRotation(Vector3(90.0f, 90.0f, 0.0f));
				break;

			}
			if (*multiIt) {
				m_janpai->SetTexture(*multiIt);
				m_janpai->Draw();
			}
		}
		dirType++;
	}
}


/**
	Ì”v•`‰æ
	@param sutehai	•\¦‚·‚éÌ”v
*/
void JanpaiManager::DrawSuteHai(std::vector<std::vector<HaiType>> suteHai) {
	Vector3 southPos = Vector3(-5.0f, 1.2f, -10.0f);
	Vector3 westPos = Vector3(-10.0f, 1.2f, 5.0f);
	Vector3 northPos = Vector3(5.0f, 1.2f, 10.0f);
	Vector3 eastPos = Vector3(10.0f, 1.2f, -5.0f);
	int southSuteCnt = 0;
	int westSuteCnt = 0;
	int northSuteCnt = 0;
	int eastSuteCnt = 0;

	int dirType = DirectionType_South;
	std::vector<std::vector<HaiType>>::const_iterator playerIt;
	std::vector<HaiType>::const_iterator it;
	for (playerIt = suteHai.begin(); playerIt != suteHai.end(); playerIt++) {
		for (it = playerIt->begin(); it != playerIt->end(); it++) {
			switch (dirType) {
			case DirectionType_South:
				m_janpai->SetPosition(southPos);
				m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
				southSuteCnt++;
				if (southSuteCnt % 6) southPos.x += 1.9f;
				if ((southSuteCnt / 6) && (southSuteCnt % 6 == 0)) {
					southPos.x = -5.0f;
					southPos.z -= 2.6f;
				}
				break;

			case DirectionType_East:
				m_janpai->SetPosition(eastPos);
				m_janpai->SetRotation(Vector3(0.0f, -90.0f, 180.0f));
				eastSuteCnt++;
				if (eastSuteCnt % 6) eastPos.z += 1.9f;
				if ((eastSuteCnt / 6) && (eastSuteCnt % 6 == 0)) {
					eastPos.z = -5.0f;
					eastPos.x += 2.6f;
				}
				break;

			case DirectionType_North:
				m_janpai->SetPosition(northPos);
				m_janpai->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
				northSuteCnt++;
				if (northSuteCnt % 6) northPos.x -= 1.9f;
				if ((northSuteCnt / 6) && (northSuteCnt % 6 == 0)) {
					northPos.x = 5.0f;
					northPos.z += 2.6f;
				}
				break;

			case DirectionType_West:
				m_janpai->SetPosition(westPos);
				m_janpai->SetRotation(Vector3(180.0f, 90.0f, 0.0f));
				westSuteCnt++;
				if (westSuteCnt % 6) westPos.z -= 1.9f;
				if ((westSuteCnt / 6) && (westSuteCnt % 6 == 0)) {
					westPos.z = 5.0f;
					westPos.x -= 2.6f;
				}
				break;

			}
			if (*it) {
				m_janpai->SetTexture(*it);
				m_janpai->Draw();
			}
		}
		dirType++;
	}

}


/**
	•›˜I”v‚ğ•`‰æ
	@param fuuroHai	•\¦‚·‚é•›˜I”v
*/
void JanpaiManager::DrawFuuroHai(std::vector<std::vector<std::shared_ptr<FuuroHai>>> fuuroHai) {
	Vector3 southPos = Vector3(31.0f, 1.2f, -31.0f);
	Vector3 westPos = Vector3(-31.0f, 1.2f, -31.0f);
	Vector3 northPos = Vector3(-31.0f, 1.2f, 31.0f);
	Vector3 eastPos = Vector3(31.0f, 1.2f, 31.0f);
	bool isFourSome = false;

	int dirType = DirectionType_South;
	std::vector<std::vector<std::shared_ptr<FuuroHai>>>::const_iterator playerIt;
	std::vector<std::shared_ptr<FuuroHai>>::const_iterator rowIt;
	std::vector<HaiType>::const_iterator colIt;
	for (playerIt = fuuroHai.begin(); playerIt != fuuroHai.end(); playerIt++) {
		for (rowIt = playerIt->begin(); rowIt != playerIt->end(); rowIt++) {
			int relativePlace = (*rowIt)->GetReceivedPlace();
			int relativePlaceOrder = 1;
			std::vector<HaiType> line = (*rowIt)->GetHais();
			if ((*rowIt)->GetHais().size() == 4) {
				isFourSome = true;
			}
			for (colIt = line.begin(); colIt != line.end(); colIt++) {
				switch (dirType) {
				case DirectionType_South:
					switch (relativePlace) {
					case RelativePlace_Right:
						if (relativePlaceOrder == RelativePlace_Right) {
							southPos.z -= 0.475f;
							m_janpai->SetPosition(southPos);
							m_janpai->SetRotation(Vector3(180.0f, 90.0f, 0.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							southPos.z += 0.475f;
							southPos.x -= 2.25f;
							m_janpai->SetPosition(southPos);
							m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									southPos.x -= 1.9f;
									m_janpai->SetPosition(southPos);
									m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							southPos.x -= 1.9f;
							m_janpai->SetPosition(southPos);
							southPos.x = 31.0f;
							southPos.z += 2.6f;
						}
						break;

					case RelativePlace_Front:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(southPos);
									southPos.x -= 1.9f;
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(southPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							southPos.x -= 2.25f;
							southPos.z -= 0.475f;
							m_janpai->SetPosition(southPos);
							m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							southPos.x -= 2.25f;
							southPos.z += 0.475f;
							m_janpai->SetPosition(southPos);
							m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
							southPos.x = 31.0f;
							southPos.z += 2.6f;
						}
						break;

					case RelativePlace_Left:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(southPos);
									southPos.x -= 1.9f;
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(southPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							southPos.x -= 1.9f;
							m_janpai->SetPosition(southPos);
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							southPos.z -= 0.475f;
							southPos.x -= 2.25f;
							m_janpai->SetPosition(southPos);
							m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
							southPos.x = 31.0f;
							southPos.z += 3.075f;
						}
						break;

					}
					break;


				case DirectionType_East:
					switch (relativePlace) {
					case RelativePlace_Right:
						if (relativePlaceOrder == RelativePlace_Right) {
							eastPos.x += 0.475f;
							m_janpai->SetPosition(eastPos);
							m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
							eastPos.z -= 2.25f;
							eastPos.x -= 0.475f;
							m_janpai->SetPosition(eastPos);
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									eastPos.z -= 1.9f;
									m_janpai->SetPosition(eastPos);
									m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							eastPos.z -= 1.9f;
							m_janpai->SetPosition(eastPos);
							eastPos.z = 31.0f;
							eastPos.x += 2.6f;
						}
						break;

					case RelativePlace_Front:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(eastPos);
									eastPos.z -= 1.9f;
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(eastPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							eastPos.z -= 2.25f;
							eastPos.x += 0.475f;
							m_janpai->SetPosition(eastPos);
							m_janpai->SetRotation(Vector3(0.0f, 0.0f, -180.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							eastPos.z -= 2.25f;
							eastPos.x -= 0.475f;
							m_janpai->SetPosition(eastPos);
							m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
							eastPos.z = 31.0f;
							eastPos.x -= 2.6f;
						}
						break;

					case RelativePlace_Left:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(eastPos);
									eastPos.z -= 1.9f;
									m_janpai->SetRotation(Vector3(180.0f, -90.0f, 0.0f));
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(eastPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							eastPos.z -= 1.9f;
							m_janpai->SetPosition(eastPos);
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							eastPos.z -= 2.25f;
							eastPos.x += 0.475f;
							m_janpai->SetPosition(eastPos);
							m_janpai->SetRotation(Vector3(0.0f, 0.0f, -180.0f));
							eastPos.z = 31.0f;
							eastPos.x -= 3.075f;
						}
						break;

					}
					break;


				case DirectionType_North:
					m_janpai->SetPosition(northPos);
					switch (relativePlace) {
					case RelativePlace_Right:
						if (relativePlaceOrder == RelativePlace_Right) {
							northPos.z += 0.475f;
							m_janpai->SetPosition(northPos);
							m_janpai->SetRotation(Vector3(0.0f, -90.0f, 180.0f));
							northPos.z -= 0.475f;
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							northPos.x += 2.25f;
							m_janpai->SetPosition(northPos);
							m_janpai->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									northPos.x += 1.9f;
									m_janpai->SetPosition(northPos);
									m_janpai->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							northPos.x += 1.9f;
							m_janpai->SetPosition(northPos);
							northPos.x = -31.0f;
							northPos.z -= 2.6f;
						}
						break;

					case RelativePlace_Front:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(northPos);
									northPos.x += 1.9f;
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(northPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							northPos.x += 2.25f;
							northPos.z += 0.475f;
							m_janpai->SetPosition(northPos);
							m_janpai->SetRotation(Vector3(0.0f, 90.0f, 180.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							northPos.x += 2.25f;
							northPos.z -= 0.475f;
							m_janpai->SetPosition(northPos);
							m_janpai->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
							northPos.x = -31.0f;
							northPos.z -= 2.6f;
						}
						break;

					case RelativePlace_Left:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(northPos);
									northPos.x += 1.9f;
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(northPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							northPos.x += 1.9f;
							m_janpai->SetPosition(northPos);
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							northPos.x += 2.25f;
							northPos.z += 0.475f;
							m_janpai->SetPosition(northPos);
							m_janpai->SetRotation(Vector3(0.0f, 90.0f, 180.0f));
							northPos.x = -31.0f;
							northPos.z -= 3.075f;
						}
						break;

					}
					break;


				case DirectionType_West:
					switch (relativePlace) {
					case RelativePlace_Right:
						if (relativePlaceOrder == RelativePlace_Right) {
							westPos.x -= 0.475f;
							m_janpai->SetPosition(westPos);
							m_janpai->SetRotation(Vector3(0.0f, 0.0f, -180.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							westPos.x += 0.475f;
							westPos.z += 2.25f;
							m_janpai->SetRotation(Vector3(180.0f, 90.0f, 0.0f));
							m_janpai->SetPosition(westPos);
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									westPos.z += 1.9f;
									m_janpai->SetPosition(westPos);
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							westPos.z += 1.9f;
							m_janpai->SetPosition(westPos);
							westPos.z = -31.0f;
							westPos.x += 2.6f;
						}
						break;


					case RelativePlace_Front:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(180.0f, 90.0f, 0.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(westPos);
									westPos.z += 1.9f;
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(westPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							westPos.z += 2.25;
							westPos.x -= 0.475f;
							m_janpai->SetPosition(westPos);
							m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							westPos.x += 0.475f;
							westPos.z += 2.25;
							m_janpai->SetPosition(westPos);
							m_janpai->SetRotation(Vector3(180.0f, 90.0f, 0.0f));
							westPos.z = -31.0f;
							westPos.x += 2.6f;
						}
						break;

					case RelativePlace_Left:
						if (relativePlaceOrder == RelativePlace_Right) {
							m_janpai->SetRotation(Vector3(180.0f, 90.0f, 0.0f));
							if (isFourSome) {
								if (*colIt != HaiType_none) {
									m_janpai->SetPosition(westPos);
									westPos.z += 1.9f;
									m_janpai->SetTexture(*colIt);
									m_janpai->Draw();
								}
								isFourSome = false;
								continue;
							}
							m_janpai->SetPosition(westPos);
						}
						else if (relativePlaceOrder == RelativePlace_Front) {
							westPos.z += 1.9f;
							m_janpai->SetPosition(westPos);
							m_janpai->SetRotation(Vector3(180.0f, 90.0f, 0.0f));
						}
						else if (relativePlaceOrder == RelativePlace_Left) {
							westPos.z += 2.25f;
							westPos.x -= 0.475f;
							m_janpai->SetPosition(westPos);
							m_janpai->SetRotation(Vector3(180.0f, 00.0f, 0.0f));
							westPos.z = -31.0f;
							westPos.x += 3.075f;
						}
						break;
					}
					break;

				}
				if (*colIt) {
					m_janpai->SetTexture(*colIt);
					m_janpai->Draw();
					relativePlaceOrder++;
				}
			}
		}
		dirType++;
	}
}


/**
	ƒcƒ‚”v‚ğ•`‰æ
	@param tsumoHai	•\¦‚·‚éƒcƒ‚”v
*/
void JanpaiManager::DrawTsumoHai(const std::vector<HaiType>& tsumoHai) {
	Vector3 southPos = Vector3(13.5f, 1.2f, -28.0f);
	Vector3 westPos = Vector3(-28.0f, 1.2f, -13.5f);
	Vector3 northPos = Vector3(-13.5f, 1.2f, 28.0f);
	Vector3 eastPos = Vector3(28.0f, 1.2f, 13.5f);

	int dirType = DirectionType_South;
	std::vector<HaiType>::const_iterator playerIt;
	for (playerIt = tsumoHai.begin(); playerIt != tsumoHai.end(); playerIt++) {
		switch (dirType) {
		case DirectionType_South:
			m_janpai->SetPosition(southPos);
			m_janpai->SetRotation(Vector3(90.0f, 0.0f, 0.0f));
			break;

		case DirectionType_East:
			m_janpai->SetPosition(eastPos);
			m_janpai->SetRotation(Vector3(-90.0f, -90.0f, 180.0f));
			break;

		case DirectionType_North:
			m_janpai->SetPosition(northPos);
			m_janpai->SetRotation(Vector3(-90.0f, 0.0f, 180.0f));
			break;

		case DirectionType_West:
			m_janpai->SetPosition(westPos);
			m_janpai->SetRotation(Vector3(90.0f, 90.0f, 0.0f));
			break;

		}
		if (*playerIt) { // ƒcƒ‚”v‚ª‚È‚©‚Á‚½‚ç•\¦‚µ‚È‚¢
			m_janpai->SetTexture(*playerIt);
			m_janpai->Draw();
		}
		dirType++;
	}
}

/**
	”v‚ÌR•`‰æŠÖ”
	@param	maxHaiCount	”v‚Ì‘”
	@param	doraSize
*/
void JanpaiManager::DrawMountainHai(int maxHaiCount, int doraSize){
	int drawHaiCount = (maxHaiCount + (doraSize - 1));
	Vector3 southMountainPos = Vector3(-20.0f, 1.0f, -20.0f);
	Vector3 eastMountainPos = Vector3(20.0f, 1.0f, -20.0f);
	Vector3 northMountainPos = Vector3(20.0f, 1.0f, 20.0f);
	Vector3 westMountainPos = Vector3(-20.0f, 1.0f, 20.0f);

	int directionCount = 0;
	int cnt = 0;
	int doraCnt = 0;
	bool visible = false;

	for (directionCount = 0; directionCount < DirectionType_Max; directionCount++){

		for (int Beside = 0; Beside < 17; Beside++){			//‰¡‚Ì”

			for (int Height = 0; Height < 2; Height++){			//c‚Ì”

				switch (directionCount){
				case DirectionType_South:
					southMountainPos.x += 1.9f - (1.9f*Height);
					southMountainPos.y = 1.0f + (1.5f*Height);
					m_janpai->SetPosition(southMountainPos);
					m_janpai->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
					break;

				case DirectionType_East:
					eastMountainPos.z += 1.9f - (1.9f*Height);
					eastMountainPos.y = 1.0f + (1.5f*Height);
					m_janpai->SetPosition(eastMountainPos);
					m_janpai->SetRotation(Vector3(0.0f, 90.0f, 0.0f));
					break;

				case DirectionType_North:
					northMountainPos.x -= 1.9f - (1.9f*Height);
					northMountainPos.y = 1.0f + (1.5f*Height);
					m_janpai->SetPosition(northMountainPos);
					m_janpai->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
					break;

				case DirectionType_West:
					westMountainPos.z -= 1.9f - (1.9f*Height);
					westMountainPos.y = 1.0f + (1.5f*Height);
					m_janpai->SetPosition(westMountainPos);
					m_janpai->SetRotation(Vector3(0.0f, 90.0f, 0.0f));
					break;
				}

				if (cnt >= START_YAMA_NUM && cnt < (drawHaiCount + START_YAMA_NUM)){
					visible = true;
				}
				else{
					visible = false;
				}

				if ((cnt + m_mahjongTilesNum) < (drawHaiCount + START_YAMA_NUM)){
					visible = true;
				}

				if (visible){
					m_janpai->Draw();
				}

				cnt++;
			}
		}
	}
}

/**
	‰¤”v‚Ì•`‰æŠÖ”
	@doras	HaiTypeŒ^‚Ìvector‚ğæ“¾
*/
void JanpaiManager::DrawDeadWall(std::vector<HaiType> doras){
	Vector3 trumpPos = Vector3(-19.0f + (1.9f * 10), 2.5f, -20.0f);

	std::vector<HaiType>::const_iterator doraIt = doras.begin();

	int doraCount = doras.size();
	int deadWallDoraCount = 0;
	int deadWallCount = 0;
	bool drawDeadWall = false;

	for (int Beside = 0; Beside < 7; Beside++){

		for (int Height = 1; Height >= 0; Height--){
			trumpPos.x += 1.9f*Height;
			trumpPos.y = 1.0f + (1.5f*Height);

			m_janpai->SetPosition(trumpPos);
			m_janpai->SetRotation(Vector3(0.0f, 0.0f, 0.0f));

			if (Beside > 1){

				if (Height){

					if (deadWallDoraCount < doraCount){

						if (*doraIt){
							m_janpai->SetTexture(*doraIt);
							doraIt++;
						}
						m_janpai->SetRotation(Vector3(180.0f, 0.0f, 0.0f));
					}
					deadWallDoraCount++;

				}
			}

			if ((doraCount - 1) <= deadWallCount){
				drawDeadWall = true;
			}

			if (drawDeadWall){
				m_janpai->Draw();
			}

			deadWallCount++;
		}

	}

}




