#include "taag.h"

void				game_engine::reset_turn(actor *target)
{
	target->get_stat()->pa.reset();
	target->get_stat()->pm.reset();
}

void				game_engine::check_alive()
{
	int		i;

	i = 0;
	while (i < (int)turn_order.size())
	{
		if (turn_order[i]->get_stat()->hp.value == 0)
		{
			this->get_cell(turn_order[i]->get_coord()->x, turn_order[i]->get_coord()->y)->p_actor = NULL;
			this->turn_order.erase(this->turn_order.begin() + i);
			this->calc = false;
			if (i < this->turn_index)
				this->turn_index--;
		}
		i++;
	}
	i = 0;
	while (i < (int)v_entity[0].size())
	{
		if (v_entity[0][i]->get_stat()->hp.value == 0)
		{
			this->get_cell(v_entity[0][i]->get_coord()->x, v_entity[0][i]->get_coord()->y)->p_actor = NULL;
			this->v_entity[0].erase(this->v_entity[0].begin() + i);
			this->calc = false;
		}
		i++;
	}
}

void				game_engine::iterate_turn_index()
{
	if (this->turn_index == -1)
	{
		this->turn_index = 0;
		this->reset_turn(get_selec_actor());
		this->calc = false;
		this->get_selec_actor()->set_cursor(3);
		this->spell_index = -1;
		this->end_turn = false;
		return ;
	}
	this->get_selec_actor()->set_cursor(this->get_selec_actor()->get_team() + 6);
	this->reset_turn(get_selec_actor());
	if (this->turn_index == (int)(this->turn_order.size() - 1))
		this->turn_index = 0;
	else
		this->turn_index++;
	this->calc = false;
	this->get_selec_actor()->set_cursor(3);
	this->spell_index = -1;
	this->end_turn = false;
}
