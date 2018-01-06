void
create_listens(char hostname[], char port[], int af) {

  struct addrinfo hints;
  struct addrinfo *local_res;
  struct addrinfo *local_res_temp;
  int count, error;
  int on = 1;
  SOCKET temp_socket;
  struct listen_elt *temp_elt;

  memset(&hints,0,sizeof(hints));
  hints.ai_family = af;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  count = 0;
  do {
    error = getaddrinfo((char *)hostname,
                        (char *)port,
                        &hints,
                        &local_res);
    count += 1;
    if (error == EAI_AGAIN) {
            sleep(1);
    }
  } while ((error == EAI_AGAIN) && (count <= 5));

  if (error) {
    return;
  }

  local_res_temp = local_res;
  while (local_res_temp != NULL) {
    temp_socket = socket(local_res_temp->ai_family,SOCK_STREAM,0);
    if (temp_socket == INVALID_SOCKET) {
        local_res_temp = local_res_temp->ai_next;
        continue;
    }

    /* happiness and joy, keep going */
    if (setsockopt(temp_socket,
		   SOL_SOCKET,
		   SO_REUSEADDR,
		   (char *)&on ,
		   sizeof(on)) == SOCKET_ERROR) { }

    /* still happy and joyful */
    if ((bind(temp_socket,
	      local_res_temp->ai_addr,
	      local_res_temp->ai_addrlen) != SOCKET_ERROR) &&
	      (listen(temp_socket,1024) != SOCKET_ERROR))  {

        /* OK, now add to the list */
        temp_elt = (struct listen_elt *)malloc(sizeof(struct listen_elt));
        if (temp_elt) {
  	           temp_elt->fd = temp_socket;
  	           if (listen_list) {
  	                 temp_elt->next = listen_list;
  	           }
  	           else {
  	                 temp_elt->next = NULL;
  	           }
  	           listen_list = temp_elt;
        } else {
        	     fprintf(stderr, "%s: could not malloc a listen_elt\n",__FUNCTION__);
        	     fflush(stderr);
        	     exit(1);
        }
    }
    local_res_temp = local_res_temp->ai_next;
  }
}
