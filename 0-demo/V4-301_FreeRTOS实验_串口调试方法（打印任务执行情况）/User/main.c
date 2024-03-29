/*
*********************************************************************************************************
*
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 本实验主要学习FreeRTOS的串口调试方法（打印任务执行情况）
*              实验目的：
*                1. 学习FreeRTOS的串口调试方法（打印任务执行情况）。
*                2. 为了获取FreeRTOS任务的执行情况，需要执行如下三个操作
*					a. 在FreeRTOSConfig.h文件中使能如下宏
*                	    #define configUSE_TRACE_FACILITY	                1
*                		#define configGENERATE_RUN_TIME_STATS               1
*                		#define configUSE_STATS_FORMATTING_FUNCTIONS        1
*                		#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()    (ulHighFrequencyTimerTicks = 0ul)
*                		#define portGET_RUN_TIME_COUNTER_VALUE()            ulHighFrequencyTimerTicks
*					b. 创建一个定时器，这个定时器的时间基准精度要高于系统时钟节拍，这样得到的任务信息才准确。
*                   c. 调用函数vTaskList和vTaskGetRunTimeStats即可获取任务任务的执行情况。
*              实验内容：
*                1. 按下按键K1可以通过串口打印任务执行情况（波特率115200，数据位8，奇偶校验位无，停止位1）
*                   =================================================
*                   任务名      任务状态 优先级   剩余栈 任务序号
*                   vTaskUserIF     R       1       318     1
*                	IDLE            R       0       118     5
*                	vTaskLED        B       2       490     2
*                	vTaskMsgPro     B       3       490     3
*               	vTaskStart      B       4       490     4
*
*                	任务名       运行计数         使用率
*                	vTaskUserIF     467             <1%
*                	IDLE            126495          99%
*                	vTaskMsgPro     1               <1%
*                	vTaskStart      639             <1%
*                	vTaskLED        0               <1%
*                  串口软件建议使用SecureCRT（V4光盘里面有此软件）查看打印信息。
*                  各个任务实现的功能如下：
*                   vTaskTaskUserIF 任务: 接口消息处理	
*                   vTaskLED        任务: LED闪烁
*                   vTaskMsgPro     任务: 消息处理，这里是用作LED闪烁
*                   vTaskStart      任务: 启动任务，也就是最高优先级任务，这里实现按键扫描
*                2. 任务运行状态的定义如下，跟上面串口打印字母B, R, D, S对应：
*                    #define tskBLOCKED_CHAR		( 'B' )  阻塞
*                    #define tskREADY_CHAR		    ( 'R' )  就绪
*                    #define tskDELETED_CHAR		( 'D' )  删除
*                    #define tskSUSPENDED_CHAR	    ( 'S' )  挂起
*              注意事项：
*                 1. 本实验推荐使用串口软件SecureCRT，要不串口打印效果不整齐。此软件在
*                    V4开发板光盘里面有。
*                 2. 务必将编辑器的缩进参数和TAB设置为4来阅读本文件，要不代码显示不整齐。
*
*	修改记录 :
*		版本号    日期         作者            说明
*       V1.0    2016-03-15   Eric2013    1. ST固件库到V3.6.1版本
*                                        2. BSP驱动包V1.2
*                                        3. FreeRTOS版本V8.2.3
*
*	Copyright (C), 2016-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"



/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
static void vTaskTaskUserIF(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
static void TaskKeyS(void *pvParameters);
/*
**********************************************************************************************************
											变量声明
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskUserIF = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
static TaskHandle_t xHandleTaskKeyS = NULL; //根据串口发过来的数据决定相应的行为的线程

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: 标准c程序入口。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
int main(void)
{
	/* 
	  在启动调度前，为了防止初始化STM32外设时有中断服务程序执行，这里禁止全局中断(除了NMI和HardFault)。
	  这样做的好处是：
	  1. 防止执行的中断服务程序中有FreeRTOS的API函数。
	  2. 保证系统正常启动，不受别的中断影响。
	  3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
	  在移植文件port.c中的函数prvStartFirstTask中会重新开启全局中断。通过指令cpsie i开启，__set_PRIMASK(1)
	  和cpsie i是等效的。
     */
	//__set_PRIMASK(1);  
	
	/* 硬件初始化 */
	bsp_Init(); 
	
	/* 1. 初始化一个定时器中断，精度高于滴答定时器中断，这样才可以获得准确的系统信息 仅供调试目的，实际项
		  目中不要使用，因为这个功能比较影响系统实时性。
	   2. 为了正确获取FreeRTOS的调试信息，可以考虑将上面的关闭中断指令__set_PRIMASK(1); 注释掉。 
	*/
	vSetupSysInfoTest();
	
	/* 创建任务 */
	AppTaskCreate();
	
    /* 启动调度，开始执行任务 */
    vTaskStartScheduler();

	/* 
	  如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
	  heap空间不足造成创建失败，此要加大FreeRTOSConfig.h文件中定义的heap大小：
	  #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
	*/
	while(1);
}

/*
*********************************************************************************************************
*	函 数 名: vPrintTaskInfo
*	功能说明: 打印任务消息。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void vPrintTaskInfo()
{
	uint8_t pcWriteBuffer1[512];
	printf("=================================================\r\n");
	printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
	vTaskList((char *)&pcWriteBuffer1);
	printf("%s\r\n", pcWriteBuffer1);

	printf("\r\n任务名\t 运行计数\t 使用率\r\n");
		
	TaskStatus_t xTaskStatusArray[10];
	UBaseType_t uxArraySize = sizeof(xTaskStatusArray) / sizeof(TaskStatus_t);
	uint32_t ulTotalRunTime = 0;
	
	UBaseType_t uxTaskCount = uxTaskGetSystemState(xTaskStatusArray,uxArraySize,&ulTotalRunTime);
	
	if(uxTaskCount == 0)
	{
		printf("uxTaskGetSystemState 失败\n");
		return ;
	}
	
	for(UBaseType_t xIndex=0;xIndex<uxTaskCount;xIndex++)
	{
		printf("%s \t ", xTaskStatusArray[xIndex].pcTaskName);  
		printf("%d \t ", xTaskStatusArray[xIndex].eCurrentState);  
		printf("%d \r\n", xTaskStatusArray[xIndex].uxCurrentPriority);  
	}
	
	//printf("Total Run Time: %lu\n", ulTotalRunTime);  
	printf("=================================================\r\n");

}

/*
*********************************************************************************************************
*	函 数 名: vTaskTaskUserIF
*	功能说明: 接口消息处理。
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 1  (数值越小优先级越低，这个跟uCOS相反)
*********************************************************************************************************
*/
static void vTaskTaskUserIF(void *pvParameters)
{
    while(1)
    {
		vPrintTaskInfo();
		vTaskDelay(2000);
	}
}

/*
*********************************************************************************************************
*	函 数 名: vTaskLED
*	功能说明: LED闪烁	
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 2  
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
    while(1)
    {
		bsp_LedToggle(2);
		printf("\r\n LED \r\n");
        vTaskDelay(200);
    }
}

/*
*********************************************************************************************************
*	函 数 名: vTaskMsgPro
*	功能说明: 信息处理，这里是用作LED闪烁	
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 3  
*********************************************************************************************************
*/
static void vTaskMsgPro(void *pvParameters)
{
    while(1)
    {
		bsp_LedToggle(3);
        vTaskDelay(300);
    }
}

/*
*********************************************************************************************************
*	函 数 名: vTaskStart
*	功能说明: 启动任务，也就是最高优先级任务，这里用作按键扫描。
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 4  
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
    while(1)
    {
		/* 按键扫描 */
		bsp_KeyScan();
        vTaskDelay(10);
    }
}


/*
*********************************************************************************************************
*	函 数 名: TaskKeyS
*	功能说明: 根据串口发过来的数据决定相应的行为的线程
*	形    参: pvParameters 是在创建该任务时传递的形参
*	返 回 值: 无
*   优 先 级: 4  
*********************************************************************************************************
*/

static void TaskKeyS(void *pvParameters)
{
    while(1)
    {
		if(PRINTINFO == 1)
		{
			vPrintTaskInfo();
			PRINTINFO = 0;
		}
		
		if(DELTASK == 1)
		{
			printf("DELTASK \r\n");
			if(xHandleTaskLED != NULL)
			{
				vTaskDelete(xHandleTaskLED);
				xHandleTaskLED = NULL;
			}

			DELTASK = 0;
		}		
		
		if(CREATETASK == 1)
		{
			printf("CREATETASK \r\n");
			if(xHandleTaskLED != NULL)
			{
				printf("已创建过LED\r\n");
			}else
			{
				xTaskCreate( vTaskLED,    		/* 任务函数  */
                 "vTaskLED",  		/* 任务名    */
                 512,         		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 2,           		/* 任务优先级*/
                 &xHandleTaskLED ); /* 任务句柄  */
			
			}

			CREATETASK = 0;
		}		
		
		if(STASK == 1)
		{
			printf("挂起任务 \r\n");
			vTaskSuspend(xHandleTaskLED);
			STASK = 0;
		}		
		
		if(RETASK == 1)
		{
			printf("恢复任务 \r\n");
			vTaskResume(xHandleTaskLED);
			RETASK = 0;
		}		
				
		vTaskDelay(10);
				
    }
}



/*
*********************************************************************************************************
*	函 数 名: AppTaskCreate
*	功能说明: 创建应用任务
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
//    xTaskCreate( vTaskTaskUserIF,   	/* 任务函数  */
//                 "vTaskUserIF",     	/* 任务名    */
//                 512,               	/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,              	/* 任务参数  */
//                 1,                 	/* 任务优先级*/
//                 &xHandleTaskUserIF );  /* 任务句柄  */
	
	
//	xTaskCreate( vTaskLED,    		/* 任务函数  */
//                 "vTaskLED",  		/* 任务名    */
//                 512,         		/* 任务栈大小，单位word，也就是4字节 */
//                 NULL,        		/* 任务参数  */
//                 2,           		/* 任务优先级*/
//                 &xHandleTaskLED ); /* 任务句柄  */
	
	xTaskCreate( vTaskMsgPro,     		/* 任务函数  */
                 "vTaskMsgPro",   		/* 任务名    */
                 512,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 3,               		/* 任务优先级*/
                 &xHandleTaskMsgPro );  /* 任务句柄  */
	
	
	xTaskCreate( vTaskStart,     		/* 任务函数  */
                 "vTaskStart",   		/* 任务名    */
                 512,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 1,              		/* 任务优先级*/
                 &xHandleTaskStart );   /* 任务句柄  */
				 
	xTaskCreate( TaskKeyS,     		/* 任务函数  */
                 "TaskKeyS",   		/* 任务名    */
                 512,            		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 4,              		/* 任务优先级*/
                 &xHandleTaskKeyS );   /* 任务句柄  */
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
