void TeleKill(void *player){
	if(player !=NULL){ 
		if(!object){
			object = new PlayerDamageable_t();
		}
		else {
			void *PhotonView = *(void**)((uint64_t)player + p_photon_offset());
			
			if(PhotonView_get_isMine(PhotonView)){
				object->m_player = player;
				object->t_MyDamageable = *(void**)((uint64_t)object->m_player + d_player_offset());
			}
			if(!PhotonView_get_isMine(PhotonView)) {
				void *damageable = *(void**)((uint64_t)player + d_player_offset());
				if(isEnemy(damageable, object->m_player)){
					object->e_player = player;
				}
			}
			if(object->e_player) {
				object->t_EnemyDamageable = *(void**)((uint64_t)object->e_player + d_player_offset());
				if(!isDead(object->t_EnemyDamageable) && !PlayerMoveC_spawnImmune(object->e_player)) { 
					Vector3 e_Pos = GetPlayerLocation(object->t_EnemyDamageable);
					Vector3 m_Pos = GetPlayerLocation(object->t_MyDamageable);
					e_Pos.z -= 1;
					Transform_set_position_Injected(PlayerDamageable_GetTransform(object->t_MyDamageable), e_Pos);
				} else {
					object->e_player = NULL;
					return;
				} 					
			}
		}
	}
}
