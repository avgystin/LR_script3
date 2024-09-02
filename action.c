action()
{
	
	web_cleanup_cookies();
	web_cache_cleanup();
	web_cleanup_auto_headers();
	
	

	lr_start_transaction("script3_start_T001");

		web_set_sockets_option("SSL_VERSION", "AUTO");

	web_url("Catalog.action", 
		"URL=https://petstore.octoperf.com/actions/Catalog.action", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("script3_start_T001", LR_AUTO);
	
	lr_rendezvous("script3_start");



	/********************* login *********************/

	lr_think_time(10);

	
	lr_start_transaction("script3_login_T002");

	web_url("Sign In", 
		"URL=https://petstore.octoperf.com/actions/Account.action;jsessionid=1DC4503E8D684AA22196678B407EA2CF?signonForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Catalog.action", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_find("Text=Welcome",
	    "SaveCount=T002Count",
		LAST);
	
	web_reg_save_param_ex(
		"ParamName=animals",
		"LB=<a href=\"/actions/Catalog.action?viewCategory=&amp;categoryId=",
		"RB=\"><img src=\"../images/",
		"Ordinal=All",
		//"SaveLen=",
		//"SaveOffset=",
		LAST);

	web_submit_data("Account.action", 
		"Action=https://petstore.octoperf.com/actions/Account.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Account.action;jsessionid=1DC4503E8D684AA22196678B407EA2CF?signonForm=", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=j2ee", ENDITEM, 
		"Name=password", "Value=j2ee", ENDITEM, 
		"Name=signon", "Value=Login", ENDITEM, 
		"Name=_sourcePage", "Value=5BuFuT0sYxbU5X9u4qCIb6V_BIuRyev4026gFzS9xo0KF_7W_XqzPJxfgunKr_J6Y4Xe5HdoeGWZcZmaVLv4GW6D7qfhW8blpvFrROqpiqY=", ENDITEM, 
		"Name=__fp", "Value=k1HbDsfUW9Rid7zKpte0R486vKOHZNeEwqlSnSgt5BwfutQvCeBFLo6DY9Ud_WtF", ENDITEM, 
		LAST);
	
	if (atoi(lr_eval_string("{T002Count}")) > 0)
	{
		lr_end_transaction("script3_login_T002", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script3_login_T002", LR_FAIL);
	}


	/********************* animals *********************/

	lr_think_time(10);
	
	RandomAnimal = lr_paramarr_random("animals");
	lr_save_string(RandomAnimal, "PRrandomAnimal");

	lr_start_transaction("script3_animal_T003");
	
	
	web_reg_find("Text=<th>Name<",
	    "SaveCount=T003Count",
		LAST);
	
	web_reg_save_param_ex(
		"ParamName=AnimalId",
		"LB=<td><a href=\"/actions/Catalog.action?viewProduct=&amp;productId=",
		"RB=\">",
		"Ordinal=All",
		//"SaveLen=",
		//"SaveOffset=",
		LAST);

	web_url("sm_dogs.gif", 
		"URL=https://petstore.octoperf.com/actions/Catalog.action?viewCategory=&categoryId={PRrandomAnimal}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Catalog.action", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
	if (atoi(lr_eval_string("{T003Count}")) > 0)
	{
		lr_end_transaction("script3_animal_T003", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script3_animal_T003", LR_FAIL);
	}
	
	
	array_size = lr_paramarr_len("animals");
	for (i = 1; i <= array_size; i++)
    {
        // Получаем текущее значение параметра массива
        char *animal = lr_paramarr_idx("animals", i);

        // Выводим значение в журнал
        lr_output_message("*********************Animal[%d]: %s", i, animal);
	}


	/********************* Product ID *********************/

	lr_think_time(10);

	lr_start_transaction("script3_bulldog_T004");
	
	web_reg_find("Text=<th>Description<",
	    "SaveCount=T004Count",
		LAST);
	
	RandomAnimalId = lr_paramarr_random("AnimalId");
	lr_save_string(RandomAnimalId, "PRrandomAnimalId");
	
	web_reg_save_param_regexp(
		"ParamName=ItemsId",
		"RegExp=workingItemId=(.*?)\"",
		"NotFound=warning",
		//"Group=2",
		"Ordinal=ALL",
		LAST);

		web_url("K9-BD-01", 
		"URL=https://petstore.octoperf.com/actions/Catalog.action?viewProduct=&productId={PRrandomAnimalId}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Catalog.action?viewCategory=&categoryId={PRrandomAnimal}", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	
	if (atoi(lr_eval_string("{T004Count}")) > 0)
	{
		lr_end_transaction("script3_bulldog_T004", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script3_bulldog_T004", LR_FAIL);
	}
	
	array_size = lr_paramarr_len("AnimalId");
	for (i = 1; i <= array_size; i++)
    {
        // Получаем текущее значение параметра массива
        char *animal = lr_paramarr_idx("AnimalId", i);

        // Выводим значение в журнал
        lr_output_message("*********************AnimalID[%d]: %s", i, animal);
	}


	/********************* ItemsId *********************/

	lr_think_time(10);

	lr_start_transaction("script3_MaleAdultBulldog_T005");
	
	ItemId = lr_paramarr_random("ItemsId");
	lr_save_string(ItemId, "PRRandomItemId");
	
	web_reg_find("Text=>Add to Cart<",
       	"SaveCount=T005Count",
		LAST);

		web_url("EST-6", 
		"URL=https://petstore.octoperf.com/actions/Catalog.action?viewItem=&itemId={PRRandomItemId}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Catalog.action?viewProduct=&productId={PRrandomAnimalId}", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);
	
	if (atoi(lr_eval_string("{T005Count}")) > 0)
	{
		lr_end_transaction("script3_MaleAdultBulldog_T005", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script3_MaleAdultBulldog_T005", LR_FAIL);
	}
	
	array_size = lr_paramarr_len("ItemsId");
	for (i = 1; i <= array_size; i++)
    {
        // Получаем текущее значение параметра массива
        char *item = lr_paramarr_idx("ItemsId", i);

        // Выводим значение в журнал
        lr_output_message("*********************item[%d]: %s", i, item);
	}


	/********************* Add to Cart *********************/

	lr_think_time(10);

	lr_start_transaction("script3_AddToCart_T006");
	
	web_reg_find("Text=Update Cart",
       	"SaveCount=T006Count",
		LAST);

		web_url("Add to Cart", 
		"URL=https://petstore.octoperf.com/actions/Cart.action?addItemToCart=&workingItemId={PRRandomItemId}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Catalog.action?viewItem=&itemId={PRRandomItemId}", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	
	if (atoi(lr_eval_string("{T006Count}")) > 0)
	{
		lr_end_transaction("script3_AddToCart_T006", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script3_AddToCart_T006", LR_FAIL);
	}


	/********************* Proceed to Checkout  *********************/

	lr_think_time(10);

	lr_start_transaction("script3_ProceedToCheckout_T007");
	
	web_reg_find("Search=Body",
		"Text=Ship to different address...",
       	"SaveCount=T007Count",
		LAST);

		web_url("Proceed to Checkout", 
		"URL=https://petstore.octoperf.com/actions/Order.action?newOrderForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Cart.action?addItemToCart=&workingItemId={PRRandomItemId}", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);
	
	if (atoi(lr_eval_string("{T007Count}")) > 0)
	{
		lr_end_transaction("script3_ProceedToCheckout_T007", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script3_ProceedToCheckout_T007", LR_FAIL);
	}


	/********************* Continue *********************/

	lr_think_time(10);

	lr_start_transaction("script3_Continue_T008");
	
	web_reg_find("Text=Please confirm the information below and then",
       	"SaveCount=T008Count",
		LAST);

		web_submit_data("Order.action", 
		"Action=https://petstore.octoperf.com/actions/Order.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Order.action?newOrderForm=", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=order.cardType", "Value=Visa", ENDITEM, 
		"Name=order.creditCard", "Value=999 9999 9999 9999", ENDITEM, 
		"Name=order.expiryDate", "Value=12/03", ENDITEM, 
		"Name=order.billToFirstName", "Value=ABC", ENDITEM, 
		"Name=order.billToLastName", "Value=XYX", ENDITEM, 
		"Name=order.billAddress1", "Value=901 San Antonio Road", ENDITEM, 
		"Name=order.billAddress2", "Value=MS UCUP02-206", ENDITEM, 
		"Name=order.billCity", "Value=Palo Alto", ENDITEM, 
		"Name=order.billState", "Value=CA", ENDITEM, 
		"Name=order.billZip", "Value=94303", ENDITEM, 
		"Name=order.billCountry", "Value=USA", ENDITEM, 
		"Name=newOrder", "Value=Continue", ENDITEM, 
		"Name=_sourcePage", "Value=LYqRJxbtLCBA2DXgnGJBZ-37lAp-6atEwWTvxHvQTa87YfcR5-NAS0X5XyigTYIrfZ-_3eN5B0PjAWSnS7T48hVy2gFiohSBlBeLp05pKIU=", ENDITEM, 
		"Name=__fp", "Value=tO5qNxYzmwMKNer2s4b_YUWwqxQLZWdhB_QafPST6nokGwdY1JW0vjcC5cseUdXPAmeTPEc6hvg0FnICZbQvuzLGtWkOiuIJwSS54rmQbpNI8qRoOVTz8A==", ENDITEM, 
		LAST);
	
	if (atoi(lr_eval_string("{T008Count}")) > 0)
	{
		lr_end_transaction("script3_Continue_T008", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script3_Continue_T008", LR_FAIL);
	}


	/********************* Confirm *********************/

	lr_think_time(10);

	lr_start_transaction("script_Confirm_T009");
	
	web_reg_find("Text=Thank you, your order has been submitted.",
       	"SaveCount=T009Count",
		LAST);

		web_url("Confirm", 
		"URL=https://petstore.octoperf.com/actions/Order.action?newOrder=&confirmed=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://petstore.octoperf.com/actions/Order.action", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		LAST);
	
	
	if (atoi(lr_eval_string("{T009Count}")) > 0)
	{
		lr_end_transaction("script_Confirm_T009", LR_AUTO);
	}
	else
	{
		lr_end_transaction("script_Confirm_T009", LR_FAIL);
	}
	
	
	iter ++;
	//vuser_id = lr_get_vuser_id();
	//vuser_attr = lr_get_vuser_ip();
	host_name = lr_get_host_name();
	lr_whoami(&vuser_id, NULL, NULL);
	
	lr_log_message("*********************Имя LG-хоста:%s, Vuser:%d, Конец итерации:%d", host_name, vuser_id, iter);
	
	

	return 0;
}