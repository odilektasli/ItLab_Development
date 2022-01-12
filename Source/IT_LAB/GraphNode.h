// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GraphNode.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class IT_LAB_API UGraphNode : public UObject
{
	GENERATED_BODY()
public:
		TArray<UGraphNode*> ChildObjects;
		TArray<UGraphNode*> ParentObjects;
		FString GateName;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graph")
		int Input1 = -1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graph")
		int Input2 = -1;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graph")
		int Output = -1;
		bool bIsVisited = false;
		bool bIsOutput = false;
		UFUNCTION(Blueprintcallable, Category = "Graph")
		virtual int CalculateOutput(bool& isCalculatable) PURE_VIRTUAL(UGraphNode::CalculateOutput, return 0;);
		void AddChild(UGraphNode* ChildToBeAdd);
		UFUNCTION(Blueprintcallable, Category = "Graph")
		virtual void SetInputValue(UGraphNode* ParentObject);
		UFUNCTION(Blueprintcallable, Category = "Graph")
		void SetOutput(bool _isOutput) { this->bIsOutput = _isOutput; }
		UFUNCTION(Blueprintcallable, Category = "Graph")
		void InitializeOutput() { this->Output = -1; }
		void ResetNodeState() { this->bIsVisited = false; Input1 = -1; Input2 = -1; }
		void UpdateParentInputs();
		bool bHasNeighbourParent = false;
		bool bIsNeighnourVisited = false;
		
		UFUNCTION(Blueprintcallable, Category = "Graph")
			void SetInput1(UGraphNode* ParentObject) { UE_LOG(LogTemp, Warning, TEXT("ParentOutput: %d, SelfInput1: %d, SelfInput2: %d, Output: %d"), ParentObject->Output, Input1, Input2, Output); this->Input1 = ParentObject->Output; }
		UFUNCTION(Blueprintcallable, Category = "Graph")
			void SetInput2(UGraphNode* ParentObject) { UE_LOG(LogTemp, Warning, TEXT("ParentOutput: %d, SelfInput1: %d, SelfInput2: %d, Output: %d"), ParentObject->Output, Input1, Input2, Output);this->Input2 = ParentObject->Output; }


private:
	int& GetAvailableInput();
	
};

UCLASS(Blueprintable)
class IT_LAB_API UVccNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UVccNode();
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UAndGateNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UAndGateNode();
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UNandGateNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UNandGateNode();
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UXorGateNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UXorGateNode();
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UXNorGateNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UXNorGateNode();
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UNorGateNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UNorGateNode();
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UOrGateNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UOrGateNode();
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UNotGateNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UNotGateNode();
	virtual void SetInputValue(UGraphNode* ParentObject) override;
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UInputOutputNode : public UGraphNode
{
	GENERATED_BODY()
public:
	UInputOutputNode();
	virtual void SetInputValue(UGraphNode* ParentObject) override;
	virtual int CalculateOutput(bool& isCalculatable) override;
};

UCLASS(Blueprintable)
class IT_LAB_API UButtonNode : public UGraphNode
{
	GENERATED_BODY()
public:
	bool IsFirstCalculation = true;
	UButtonNode();
	virtual void SetInputValue(UGraphNode* ParentObject) override;
	virtual int CalculateOutput(bool& isCalculatable) override;
	UFUNCTION(Blueprintcallable, Category = "Graph")
	void bpSetInputValue(UGraphNode* ParentObject);
};


UCLASS(Blueprintable)
class IT_LAB_API UGraph : public UObject
{
	GENERATED_BODY()

protected:

	TArray<UGraphNode*> NodeList;
	TArray<UGraphNode*> TotalNodeList;

	TMap<FString, int32> OrderMap =
								{
									{TEXT("VCCNode"), 0},
									{TEXT("AndGate"), 0},
									{TEXT("XorGate"), 0},
									{TEXT("OrGate"), 0},
									{TEXT("NotGate"), 0},
									{TEXT("InputOutput"), 0},
									{TEXT("Button"), 0},
									{TEXT("NandGate"), 0},
									{TEXT("NorGate"), 0},
									{TEXT("XNorGate"), 0}

								};
	

public:

	UGraphNode* RootNode;
	TMap<FString, UGraphNode*> NodeMap;
	UFUNCTION(Blueprintcallable, Category = "Graph")
	void SetRootNode(UGraphNode* IncomingRootNode, UGraphNode*& IncomingRootNodeOut);

	UFUNCTION(Blueprintcallable, Category = "Graph")
	void AddEdge(UGraphNode* From, UGraphNode* To, UGraphNode*& FromOut, UGraphNode*& ToOut);

	UFUNCTION(Blueprintcallable, Category = "Graph")
		void RemoveEdge(UGraphNode* GraphNode, UGraphNode* ParentGraphNode);

	UFUNCTION(Blueprintcallable, Category = "Graph")
	void CalculateGraphOutput();
	void ResetGraphState(UGraphNode*& rootNode);
	UFUNCTION(Blueprintcallable, Category = "Graph")
	void UpdateGraph() ;
	UFUNCTION(Blueprintcallable, Category = "Graph")
		void RemoveComponent(UGraphNode* GraphNode);
	UFUNCTION(BlueprintPure, Category = "Graph")
	UGraphNode* GetNodeByName(FString gateName);
private:
	//TArray<UGraphNode* > CopyNodeList;
	void InitializeGraph();

};
