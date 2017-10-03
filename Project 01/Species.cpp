


class Species
{
private:
	int identifier = 1;	//Number used to idenify this species on any square of the any Board
	int reqAdj = 3;		//Number of adjacent "living" squares needed for any square of this species to stay alive

	//************************************************

public:
	int GetIdentifer()
	{
		return identifier;
	}

	//************************************************

	int GetReqAdj()
	{
		return reqAdj;
	}
};