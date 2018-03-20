// hellorpc_c.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "hello.h"

int _tmain(int argc, _TCHAR* argv[])
{
	RPC_STATUS status;
	unsigned char *pszString = (unsigned char *)"Hello World!\0";
	unsigned char *pszBindStr = NULL;
	status = RpcStringBindingCompose(NULL, (unsigned char *)PROTOCOL_SEQUENCE, NULL, (unsigned char *)END_POINT, NULL, &pszBindStr);
	if(status) {
		exit(GetLastError());
	}
	
	status = RpcBindingFromStringBinding(pszBindStr, &hello_IfHandle);
	if(status) {
		exit(GetLastError());
	}
	RpcTryExcept {
		HelloProc(pszString);  // Զ�̵���
		Shutdown();  // ����˹ر�
	}
	RpcExcept(1) {
		printf("Զ�̵��÷����쳣���쳣������:%ld", RpcExceptionCode());
	}
	RpcEndExcept

	//ִ��Զ���ڴ��ͷ�
	status = RpcStringFree(&pszBindStr);  // remote calls done; unbind
	if (status) {
		exit(status);
	}
	//ִ��unbind
	status = RpcBindingFree(&hello_IfHandle);  // remote calls done; unbind
	if (status) {
		exit(status);
	}
	return 0;
}

/*********************************************************************/
/*                MIDL allocate and free                             */
/*********************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
	return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
	free(ptr);
}