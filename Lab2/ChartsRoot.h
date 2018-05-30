#pragma once
#include "TStack.h"

using namespace System::Drawing;

class ChartRoot
{
protected:
	bool Visible;
	bool Active;
	bool sm;

public:
	ChartRoot()
	{
		Visible = true;
		Active = false;
		sm = false;
	};

	bool IsVisible()
	{
		return Visible;
	};

	bool IsActive()
	{
		return Active;
	};

	void SetActive(bool _Active = true)
	{
		Active = _Active;
	};

	void SetVisible(bool _Visible = true)
	{
		Visible = _Visible;
	};

	bool GetActive()
	{
		return Active;
	};

	bool GetVisible()
	{
		return Visible;
	};

	bool Get()
	{
		return sm;
	}

	void Set(bool _sm)
	{
		sm = _sm;
	}

	virtual void Show(Graphics^ gr, Pen^ pen) = 0;
	virtual void Hide(Graphics^ gr, Pen^ pen) = 0;
};

class ChartPoint : public ChartRoot
{
protected:
	int x, y;

public:

	ChartPoint(int _x = 0, int _y = 0)
	{
		x = _x; y = _y;
	}

	virtual void Show(Graphics^ gr, Pen^ pen)
	{
		gr->DrawEllipse(pen, (int)(x - 6), (int)(y - 6), 12, 12);

		Visible = true;
	}

	virtual void Hide(Graphics^ gr, Pen^ pen)
	{
		gr->DrawEllipse(Pens::White, (int)(x - 6), int(y - 6), 12, 12);
		Visible = false;
	}

	int GetX()
	{
		return x - 2 > 0 ? x - 2 : 0;
	}
	int GetY()
	{
		return y - 2 > 0 ? y - 2 : 0;
	}

	void SetX(int _x) { x = _x; }
	void SetY(int _y) { y = _y; }
};

class Chart;
struct ChartLine
{
	Chart* pLine;
	ChartPoint* pF;
	ChartPoint* pL;
};

class Chart : public ChartRoot
{
protected:
	ChartRoot * pFirst;
	ChartRoot *pLast;
	TStack<ChartLine> St;
public:

	Chart(ChartRoot* _pFirst = NULL, ChartRoot* _pLast = NULL)
	{
		pFirst = _pFirst; pLast = _pLast; this->Visible = true;
	}

	void SetFirst(ChartRoot *pf)
	{
		ChartPoint *p = dynamic_cast<ChartPoint*>(pf);
		Chart *c = dynamic_cast<Chart*>(pf);

		if (!p || !c)
			pFirst = pf;
	}
	void SetLast(ChartRoot *pf)
	{
		ChartPoint *p = dynamic_cast<ChartPoint*>(pf);
		Chart *c = dynamic_cast<Chart*>(pf);

		if (!p || !c)
			pLast = pf;
	}

	ChartRoot* GetFirst()
	{
		return pFirst;
	}

	ChartRoot* GetLast()
	{
		return pLast;
	}

	ChartRoot* Show(Graphics^ gr, Pen^ pen, ChartRoot* p)
	{
		ChartPoint *pF, *pL;
		Chart *pNode;

		if (dynamic_cast<ChartPoint*>(p))
			return p;
		else
		{
			pNode = dynamic_cast<Chart*>(p);
			pF = dynamic_cast<ChartPoint*>(Show(gr, pen, pNode->pFirst));
			pL = dynamic_cast<ChartPoint*>(Show(gr, pen, pNode->pLast));
			gr->DrawLine(pen, (int)(pF->GetX()), (int)(pF->GetY()), (int)(pL->GetX()), (int)(pL->GetY()));

			return pL;
		}
	}

	void Show(Graphics^ gr, Pen^ pen);
	void Hide(Graphics^ gr, Pen^ pen);
	ChartPoint* SetCurrPoint(Graphics^ gr, Pen^ pen, int _x, int _y);
	void AddLine(Graphics^ gr, Pen^ pen, ChartPoint* PointActive, Chart* NewLine);

	virtual void MoveTo(int X, int Y)
	{
		ChartLine CurrLine;
		ChartRoot* pR;
		ChartPoint* pP;
		CurrLine.pLine = this;
		CurrLine.pF = NULL;
		CurrLine.pL = NULL;
		St.Clear();
		St.Push(CurrLine);

		while (!St.Empty())
		{
			CurrLine = St.Pop();
			while (CurrLine.pF == NULL)
			{
				pR = CurrLine.pLine->GetFirst();
				pP = dynamic_cast<ChartPoint*>(pR);
				if (pP != NULL)
					CurrLine.pF = pP;
				else
				{
					St.Push(CurrLine);
					CurrLine.pLine = dynamic_cast<Chart*>(pR);
				}
			}

			if (CurrLine.pL == NULL)
			{
				pR = CurrLine.pLine->GetLast();
				pP = dynamic_cast<ChartPoint*>(pR);
				if (pP != NULL)
					CurrLine.pL = pP;
				else
				{
					St.Push(CurrLine);
					CurrLine.pLine = dynamic_cast<Chart*>(pR);
					CurrLine.pF = NULL;
					St.Push(CurrLine);
				}
			}
			CurrLine.pLine->SetVisible(true);

			if (CurrLine.pF != NULL && CurrLine.pL != NULL)
			{
				if (!CurrLine.pF->Get())
				{
					CurrLine.pF->Set(true);
					CurrLine.pF->SetX(CurrLine.pF->GetX() + X);
					CurrLine.pF->SetY(CurrLine.pF->GetY() + Y);
				}
				if (!CurrLine.pL->Get())
				{
					CurrLine.pL->Set(true);
					CurrLine.pL->SetX(CurrLine.pL->GetX() + X);
					CurrLine.pL->SetY(CurrLine.pL->GetY() + Y);
				}

				pP = CurrLine.pL;
				if (!St.Empty())
				{
					CurrLine = St.Pop();
					if (CurrLine.pF == NULL)
						CurrLine.pF = pP;
					else
						CurrLine.pL = pP;
					St.Push(CurrLine);
				}
			}
		}
	}
	virtual void Reset()
	{
		ChartLine CurrLine;
		ChartRoot* pR;
		ChartPoint* pP;
		CurrLine.pLine = this;
		CurrLine.pF = NULL;
		CurrLine.pL = NULL;
		St.Clear();
		St.Push(CurrLine);

		while (!St.Empty())
		{
			CurrLine = St.Pop();
			while (CurrLine.pF == NULL)
			{
				pR = CurrLine.pLine->GetFirst();
				pP = dynamic_cast<ChartPoint*>(pR);
				if (pP != NULL)
					CurrLine.pF = pP;
				else
				{
					St.Push(CurrLine);
					CurrLine.pLine = dynamic_cast<Chart*>(pR);
				}
			}

			if (CurrLine.pL == NULL)
			{
				pR = CurrLine.pLine->GetLast();
				pP = dynamic_cast<ChartPoint*>(pR);
				if (pP != NULL)
					CurrLine.pL = pP;
				else
				{
					St.Push(CurrLine);
					CurrLine.pLine = dynamic_cast<Chart*>(pR);
					CurrLine.pF = NULL;
					St.Push(CurrLine);
				}
			}
			CurrLine.pLine->SetVisible(true);

			if (CurrLine.pF != NULL && CurrLine.pL != NULL)
			{
				CurrLine.pF->Set(false);
				CurrLine.pL->Set(false);

				pP = CurrLine.pL;
				if (!St.Empty())
				{
					CurrLine = St.Pop();
					if (CurrLine.pF == NULL)
						CurrLine.pF = pP;
					else
						CurrLine.pL = pP;
					St.Push(CurrLine);
				}
			}
		}
	}
};

void Chart::Show(Graphics ^gr, Pen ^pen)
{
	ChartLine CurrLine;
	ChartRoot* pR;
	ChartPoint* pP;
	CurrLine.pLine = this;
	CurrLine.pF = NULL;
	CurrLine.pL = NULL;
	St.Clear();
	St.Push(CurrLine);

	while (!St.Empty())
	{
		CurrLine = St.Pop();
		while (CurrLine.pF == NULL)
		{
			pR = CurrLine.pLine->GetFirst();
			pP = dynamic_cast<ChartPoint*>(pR);
			if (pP != NULL)
				CurrLine.pF = pP;
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
			}
		}

		if (CurrLine.pL == NULL)
		{
			pR = CurrLine.pLine->GetLast();
			pP = dynamic_cast<ChartPoint*>(pR);
			if (pP != NULL)
				CurrLine.pL = pP;
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
				CurrLine.pF = NULL;
				St.Push(CurrLine);
			}
		}
		CurrLine.pLine->SetVisible(true);

		if (CurrLine.pF != NULL && CurrLine.pL != NULL)
		{
			if (CurrLine.pLine->GetVisible())
			{
				gr->DrawLine(pen, CurrLine.pF->GetX(), CurrLine.pF->GetY(), CurrLine.pL->GetX(), CurrLine.pL->GetY());
				CurrLine.pF->Show(gr, pen);
				CurrLine.pL->Show(gr, pen);
			}

			pP = CurrLine.pL;
			if (!St.Empty())
			{
				CurrLine = St.Pop();
				if (CurrLine.pF == NULL)
					CurrLine.pF = pP;
				else
					CurrLine.pL = pP;
				St.Push(CurrLine);
			}
		}
	}
}

void Chart::Hide(Graphics^ gr, Pen^ pen)
{
	ChartLine CurrLine;
	ChartRoot* pR;
	ChartPoint* pP;
	CurrLine.pLine = this;
	CurrLine.pF = NULL;
	CurrLine.pL = NULL;
	St.Clear();
	St.Push(CurrLine);

	while (!St.Empty())
	{
		CurrLine = St.Pop();
		while (CurrLine.pF == NULL)
		{
			pR = CurrLine.pLine->GetFirst();
			pP = dynamic_cast<ChartPoint*>(pR);
			if (pP != NULL)
				CurrLine.pF = pP;
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
			}
		}
		if (CurrLine.pL == NULL)
		{
			pR = CurrLine.pLine->GetLast();
			pP = dynamic_cast<ChartPoint*>(pR);
			if (pP != NULL)
				CurrLine.pL = pP;
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
				CurrLine.pF = NULL;
				St.Push(CurrLine);
			}
		}

		if (CurrLine.pF != NULL && CurrLine.pL != NULL)
		{
			gr->DrawLine(pen, CurrLine.pF->GetX(), CurrLine.pF->GetY(), CurrLine.pL->GetX(), CurrLine.pL->GetY());
			CurrLine.pF->Show(gr, pen);
			CurrLine.pL->Show(gr, pen);

			pP = CurrLine.pL;
			if (!St.Empty())
			{
				CurrLine = St.Pop();
				if (CurrLine.pF == NULL)
					CurrLine.pF = pP;
				else
					CurrLine.pL = pP;
				St.Push(CurrLine);
			}
		}
	}
}

ChartPoint* Chart::SetCurrPoint(Graphics^ gr, Pen^ pen, int _x, int _y)
{
	ChartPoint* PointActive = new ChartPoint;;
	ChartLine CurrLine;
	ChartRoot* pR;
	ChartPoint* pP;
	CurrLine.pLine = this;
	CurrLine.pF = CurrLine.pL = NULL;

	St.Clear();
	St.Push(CurrLine);
	PointActive->SetX(-1); PointActive->SetY(-1);

	while (!St.Empty())
	{
		CurrLine = St.Pop();
		while (CurrLine.pF == NULL)
		{
			pR = CurrLine.pLine->GetFirst();
			pP = dynamic_cast<ChartPoint*>(pR);
			if (pP != NULL)
			{
				CurrLine.pF = pP;
				CurrLine.pF->SetActive(false);
				CurrLine.pF->Show(gr, pen);

				if (abs(_x - CurrLine.pF->GetX())<10 && abs(_y - CurrLine.pF->GetY())<10)
				{
					CurrLine.pF->SetActive(true);
					PointActive = CurrLine.pF;
				}
			}
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
			}
		}
		if (CurrLine.pL == NULL)
		{
			pR = CurrLine.pLine->GetLast();
			pP = dynamic_cast<ChartPoint*>(pR);

			if (pP != NULL)
			{
				CurrLine.pL = pP;
				CurrLine.pL->SetActive(false);
				CurrLine.pL->Show(gr, pen);

				if (abs(_x - CurrLine.pL->GetX())<3 && abs(_y - CurrLine.pL->GetY())<3)
				{
					CurrLine.pL->SetActive(true);
					PointActive = CurrLine.pL;
				}
			}
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
				CurrLine.pF = NULL;
				St.Push(CurrLine);
			}
		}
		if (CurrLine.pF != NULL && CurrLine.pL != NULL)
		{
			pP = CurrLine.pL;

			if (!St.Empty())
			{
				CurrLine = St.Pop();
				if (CurrLine.pF == NULL)
					CurrLine.pF = pP;
				else
					CurrLine.pL = pP;

				St.Push(CurrLine);
			}
		}
	}

	PointActive->Show(gr, pen);
	return PointActive;
}

void Chart::AddLine(System::Drawing::Graphics ^gr, System::Drawing::Pen ^pen, ChartPoint *PointActive, Chart* NewLine)
{
	ChartLine CurrLine;
	ChartRoot* pR;
	ChartPoint* pP;
	CurrLine.pLine = this;
	CurrLine.pF = NULL;
	CurrLine.pL = NULL;

	St.Clear();
	St.Push(CurrLine);

	while (!St.Empty())
	{
		CurrLine = St.Pop();
		while (CurrLine.pF == NULL)
		{
			pR = CurrLine.pLine->GetFirst();
			pP = dynamic_cast<ChartPoint*>(pR);

			if (pP != NULL)
			{
				CurrLine.pF = pP;
				if (abs(PointActive->GetX() - CurrLine.pF->GetX())<3 && abs(PointActive->GetY() - CurrLine.pF->GetY())<3)
				{
					CurrLine.pLine->SetFirst(NewLine);
					return;
				}
			}
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
			}
		}
		if (CurrLine.pL == NULL)
		{
			pR = CurrLine.pLine->GetLast();
			pP = dynamic_cast<ChartPoint*>(pR);

			if (pP != NULL)
			{
				CurrLine.pL = pP;
				if (abs(PointActive->GetX() - CurrLine.pL->GetX())<3 && abs(PointActive->GetY() - CurrLine.pL->GetY())<3)
				{
					CurrLine.pLine->SetLast(NewLine);
					return;
				}
			}
			else
			{
				St.Push(CurrLine);
				CurrLine.pLine = dynamic_cast<Chart*>(pR);
				CurrLine.pF = NULL;
				St.Push(CurrLine);
			}
		}
		if (CurrLine.pF != NULL && CurrLine.pL != NULL)
		{
			pP = CurrLine.pL;

			if (!St.Empty())
			{
				CurrLine = St.Pop();

				if (CurrLine.pF == NULL)
					CurrLine.pF = pP;
				else
					CurrLine.pL = pP;

				St.Push(CurrLine);
			}
		}
	}
}