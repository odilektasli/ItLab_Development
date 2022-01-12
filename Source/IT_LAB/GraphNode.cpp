  // Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNode.h"



int UAndGateNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1 || ParentObjects[1]->Output == -1) isCalculatable = false;
	if (ParentObjects[0]->Output == 1 && ParentObjects[1]->Output == 1)
	{
		Output = 1;
		
	}

	else
	{
		Output = 0;
	}
 	return Output;
	//return (int)(Input1 & Input2);
}

int UNandGateNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1 || ParentObjects[1]->Output == -1) isCalculatable = false;
	if (ParentObjects[0]->Output == 1 && ParentObjects[1]->Output == 1)
	{
		Output = 0;

	}

	else
	{
		Output = 1;
	}
	return Output;
	//return (int)(Input1 & Input2);
}

int UXorGateNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1 || ParentObjects[1]->Output == -1) isCalculatable = false;
	Output = (int)(ParentObjects[0]->Output != ParentObjects[1]->Output);
	return Output;
}

int UOrGateNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1 || ParentObjects[1]->Output == -1) isCalculatable = false;
	if (ParentObjects[0]->Output == 0 && ParentObjects[1]->Output == 0)
	{
		Output = 0;
	}
	else
	{
		Output = 1;
	}
	return Output;
}

UVccNode::UVccNode()
{
	GateName = "VCCNode";
	Input1 = Input2 = Output = 1;
	UE_LOG(LogTemp, Warning, TEXT("IAAAAA I1:%d I2:%d Ou:%d"), Input1, Input2, Output);
}

int UVccNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (Input1 == -1 || Input2 == -1) isCalculatable = false;
	Output = 1;
	return Output;
	
}
void UNotGateNode::SetInputValue(UGraphNode* ParentObject)
{
	Input1 = Input2 = ParentObject->Output;
	Output = Input1;
}
int UNotGateNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1 ) isCalculatable = false;
	Output = !ParentObjects[0]->Output;
	return Output;
}

void UInputOutputNode::SetInputValue(UGraphNode* ParentObject)
{
	if (ParentObject)
	{
		Output = Input1 = Input2 = ParentObject->Output;

	} 
	else {
		Output = Input1 = Input2 = -1;
	}
}

int UInputOutputNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1)
	{
		isCalculatable = false;
	}
	else
	{
		this->SetInputValue(ParentObjects[0]);
	
	}
	return Output;

}

void UButtonNode::SetInputValue(UGraphNode* ParentObject)
{
	
	if (IsFirstCalculation)
	{

		Output = Input1 = Input2 = ParentObject->Output;
	} 
	else
	{
		Output = !ParentObject->Output;
	}
}

int UButtonNode::CalculateOutput(bool& isCalculatable)
{
	if (IsFirstCalculation)
	{
		isCalculatable = true;
		if (Input1 == -1 || Input2 == -1) isCalculatable = false;
		IsFirstCalculation = false;
	}
	else 
	{
		isCalculatable = true;
		if (Input1 == -1 || Input2 == -1) isCalculatable = false;
	
	
	}
	return this->Output;
}

void UButtonNode::bpSetInputValue(UGraphNode* ParentObject)
{
	this->SetInputValue(ParentObject);
}

UAndGateNode::UAndGateNode()
{
	GateName = "AndGate";
}

UNandGateNode::UNandGateNode()
{
	GateName = "NandGate";
}

UXorGateNode::UXorGateNode()
{
	GateName = "XorGate";
}

UOrGateNode::UOrGateNode()
{
	GateName = "OrGate";
}

UNotGateNode::UNotGateNode()
{
	GateName = "NotGate";
}

UInputOutputNode::UInputOutputNode()
{
	GateName = "InputOutput";
}

UButtonNode::UButtonNode()
{
	GateName = "Button";
}

UNorGateNode::UNorGateNode()
{
	GateName = "NorGate";
}

UXNorGateNode::UXNorGateNode()
{
	GateName = "XNorGate";
}
//UAndGateNode::UAndGateNode()
//{
//	GateName = "AndGate";
//}
//
//UXorGateNode::UXorGateNode()
//{
//	GateName = "XORGate";
//}
//UGraphNode::UGraphNode()
//{
//
//}



///


void UGraphNode::AddChild(UGraphNode* ChildToBeAdd)
{
	ChildObjects.AddUnique(ChildToBeAdd);
	ChildToBeAdd->ParentObjects.Add(this);
	
}

int& UGraphNode::GetAvailableInput()
{
	if (Input1 == -1)
	{
		return Input1;
	}
	else 
	{
		return Input2;
	}

}

//Sets input by taking the GraphNodeObject considering as parent object
void UGraphNode::SetInputValue(UGraphNode* ParentObject)
{
	int& SelectedInput = GetAvailableInput();

	SelectedInput = ParentObject->Output;
	
	//UE_LOG(LogTemp, Warning, TEXT("Output: %s, %d"), *(GateName), (SelectedInput));
	
}

//////

void UGraph::SetRootNode(UGraphNode* IncomingRootNode, UGraphNode*& IncomingRootNodeOut)
{
	RootNode = IncomingRootNode;
	IncomingRootNodeOut = IncomingRootNode;

}

void UGraph::AddEdge(UGraphNode* From, UGraphNode* To, UGraphNode*& FromOut,  UGraphNode*& ToOut)
{
	From->AddChild(To);	
	To->SetInputValue(From);
	int32* GateIndex = OrderMap.Find(To->GateName);
	(*GateIndex)++;

	UE_LOG(LogTemp, Warning, TEXT("GATEINDEX: %d"), (*GateIndex));
	FString GateNameKey = FString(To->GateName).Append(FString::FromInt(*GateIndex));
	
		NodeMap.Add(GateNameKey, To);
	
	FromOut = From;
	ToOut = To;
}

void UGraph::RemoveEdge(UGraphNode* GraphNode, UGraphNode* ParentGraphNode)
{
	if (GraphNode)
	{
		for (auto* ParentObject : GraphNode->ParentObjects)
		{
			ParentObject->ChildObjects.Remove(GraphNode);
		}
		for (auto* ChildObject : GraphNode->ChildObjects)
		{
			ChildObject->ParentObjects.Remove(GraphNode);
		}
		GraphNode->ChildObjects.Empty();
		GraphNode->ParentObjects.Empty();
	}
	

	/*if (TotalNodeList.Contains(GraphNode)) { TotalNodeList.Remove(GraphNode); }*/
}

UGraphNode* UGraph::GetNodeByName(FString gateName)
{
	UGraphNode** foundNode = nullptr;
	foundNode = NodeMap.Find(gateName);
	if (foundNode)
	{
		return *foundNode;

	}
	else return nullptr;
}

void UGraph::CalculateGraphOutput()
{
	NodeList.Empty();
	int32 FailSafe = 0;
	NodeList.Add(RootNode);
	//for (UGraphNode* eachnode : NodeList)
	//{
	//	eachnode->ResetNodeState();
	//}
	/*UE_LOG(LogTemp, Error, TEXT("NodeListCount: %d"), (NodeList.Num()));
	RootNode->bIsVisited = false;*/
	/*CopyNodeList  = NodeList;*/
	while (NodeList.Num() != 0 )
	{
		UGraphNode* CurrentNode = NodeList[0];
		bool canCalculate = false;
		TotalNodeList.AddUnique(CurrentNode);
		/*TotalNodeListBackup.AddUnique(&(*CurrentNode));*/
		
			CurrentNode->CalculateOutput(canCalculate);
			
			/*	UE_LOG(LogTemp, Warning, TEXT("Gate: %s, Input1: %d, Input2:, %d, Output:, %d"), *(CurrentNode->GateName), (CurrentNode->Input1), (CurrentNode->Input2), (CurrentNode->Output));
				UE_LOG(LogTemp, Warning, TEXT("Output: %s, %d, %s"), *(CurrentNode->GateName), (CurrentNode->Output), (canCalculate? TEXT("True") : TEXT("False")));
				break;*/

			if ((canCalculate && !CurrentNode->bIsVisited) || CurrentNode->Output != -1)
			{

				if (CurrentNode->bIsOutput && CurrentNode->Output != -1)
				{
					UE_LOG(LogTemp, Warning, TEXT("Output: %s, %d, %s"), *(CurrentNode->GateName), (CurrentNode->Output), (canCalculate ? TEXT("True") : TEXT("False")));

				}
				CurrentNode->bIsVisited = true;

				if (CurrentNode->ChildObjects.Num() != 0)
				{
					for (auto* ChildObject : CurrentNode->ChildObjects)
					{
						NodeList.AddUnique(ChildObject);
						UE_LOG(LogTemp, Warning, TEXT("Output: %s, %d, %d"), *(CurrentNode->GateName), (CurrentNode->Output), (canCalculate));

						UE_LOG(LogTemp, Warning, TEXT("Size:%d"), CurrentNode->ChildObjects.Num());
					}
				}

				NodeList.Remove(CurrentNode);
			}
			
			if (!canCalculate)
			{
				UE_LOG(LogTemp, Warning, TEXT("NAME: %s"), *CurrentNode->GateName);
				
				for (auto* ParentObject : CurrentNode->ParentObjects)
				{
					CurrentNode->SetInputValue(ParentObject);
					CurrentNode->CalculateOutput(canCalculate);
					//UE_LOG(LogTemp, Warning, TEXT("Size:%d"), CurrentNode->ChildObjects.Num());
				}

				NodeList.Remove(CurrentNode);
				NodeList.Add(CurrentNode);
			}


		
			FailSafe++;
		}
		/*UE_LOG(LogTemp, Warning, TEXT("Output: %s, %d, %d"), *(CurrentNode->GateName), (CurrentNode->Output), (canCalculate));*/

		
	

	/*RootNode->CalculateOutput();*/
}

void UGraph::InitializeGraph()
{
	
}



void UGraph::UpdateGraph()
{
	

	/*for (auto* CurrentNode : TotalNodeList)
	{
		CurrentNode->bIsVisited = false;

		if (!(CurrentNode->IsA(UVccNode::StaticClass()) ||  CurrentNode->IsA(UButtonNode::StaticClass())))
		{
			CurrentNode->Output = -1;
			
		}
			
		
	}*/
	
	bool lock = true;

	for (int32 Index = 0; Index < TotalNodeList.Num(); Index++)
	{
		TotalNodeList[Index]->bIsVisited = false;

		if (!(TotalNodeList[Index]->IsA(UVccNode::StaticClass()) || TotalNodeList[Index]->IsA(UButtonNode::StaticClass())))
		{
			TotalNodeList[Index]->Output = -1;

		}
	}

	lock = false;

	if (!lock)
	{
		CalculateGraphOutput();
	}
	

}

void UGraph::RemoveComponent(UGraphNode* GraphNode)
{
	for (auto* ParentObject : GraphNode->ParentObjects)
	{
		ParentObject->ChildObjects.Remove(GraphNode);
	}
	GraphNode->ParentObjects.Empty();
	GraphNode->ChildObjects.Empty();
	TotalNodeList.Remove(GraphNode);
}

void UGraphNode::UpdateParentInputs()
{
	if (ParentObjects.Num() > 1)
	{
		Input1 = ParentObjects[0]->Output;
		Input2 = ParentObjects[1]->Output;

	}
	else
	{
		Input1 = Input2 = ParentObjects[0]->Output;
	}

}

int UXNorGateNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1 || ParentObjects[1]->Output == -1) isCalculatable = false;
	Output = (int)(ParentObjects[0]->Output == ParentObjects[1]->Output);
	return Output;
}

int UNorGateNode::CalculateOutput(bool& isCalculatable)
{
	isCalculatable = true;
	if (ParentObjects[0]->Output == -1 || ParentObjects[1]->Output == -1) isCalculatable = false;
	if (ParentObjects[0]->Output == 0 && ParentObjects[1]->Output == 0)
	{
		Output = 1;
	}
	else
	{
		Output = 0;
	}
	return Output;
}
