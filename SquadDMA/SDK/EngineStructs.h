#include <iostream>
#include <tuple>
#pragma once

struct UEVector {
	float x; 
	float y;
	float z;
};
struct UERotator {
	float Pitch;
	float Yaw;
	float Roll;
};
struct ViewMatrixStruct {
	float _0;
	float _1;
	float _2;
	float _3;
	float _4;
	float _5;
	float _6;
	float _7;
	float _8;
	float _9;
	float _10;
	float _11;
	float _12;
	float _13;
	float _14;
	float _15;
	float _16;
};

struct m3x4 {
	float _1, _2, _3, _4;
	float _5, _6, _7, _8;
	float _9, _10, _11, _12;
};

struct bone_struct {
	m3x4 Pelvis;
	m3x4 Spine;
	m3x4 Spine1;
	m3x4 Spine2;
	m3x4 Spine4;
	m3x4 Neck1;
	m3x4 Head1;
	m3x4 forward;
	m3x4 R_Clavicle;
	m3x4 R_UpperArm;
	m3x4 R_Forearm;
	m3x4 R_Hand;
	m3x4 Anim_Attachment_RH;
	m3x4 L_Clavicle;
	m3x4 L_UpperArm;
	m3x4 L_Forearm;
	m3x4 L_Hand;
	m3x4 Anim_Attachment_LH;
	m3x4 R_Thigh;
	m3x4 R_Calf;
	m3x4 R_Foot;
	m3x4 R_Toe0;
	m3x4 L_Thigh;
	m3x4 L_Calf;
	m3x4 L_Foot;
	m3x4 L_Toe0;
	m3x4 L_Finger4;
	m3x4 L_Finger41;
	m3x4 L_Finger42;
	m3x4 L_Finger3;
	m3x4 L_Finger31;
	m3x4 L_Finger32;
	m3x4 L_Finger2;
	m3x4 L_Finger21;
	m3x4 L_Finger22;
	m3x4 L_Finger1;
	m3x4 L_Finger11;
	m3x4 L_Finger12;
	m3x4 L_Finger0;
	m3x4 L_Finger01;
	m3x4 L_Finger02;
	m3x4 R_Finger4;
	m3x4 R_Finger41;
	m3x4 R_Finger42;
	m3x4 R_Finger3;
	m3x4 R_Finger31;
	m3x4 R_Finger32;
	m3x4 R_Finger2;
	m3x4 R_Finger21;
	m3x4 R_Finger22;
	m3x4 R_Finger1;
	m3x4 R_Finger11;
	m3x4 R_Finger12;
	m3x4 R_Finger0;
	m3x4 R_Finger01;
	m3x4 R_Finger02;
	m3x4 L_Elbow;
	m3x4 L_Ulna;
	m3x4 R_Ulna;
	m3x4 L_Pectoral;
	m3x4 R_Shoulder;
	m3x4 L_Shoulder;
	m3x4 R_Trapezius;
	m3x4 R_Wrist;
	m3x4 R_Bicep;
	m3x4 L_Bicep;
	m3x4 L_Trapezius;
	m3x4 L_Wrist;
	m3x4 R_Elbow;
};

enum class bones : int {
	Pelvis = 0,
	Spine = 1,
	Spine1 = 2,
	Spine2 = 3,
	Spine4 = 4,
	Neck1 = 5,
	Head1 = 6,
	forward = 7,
	R_Clavicle = 8,
	R_UpperArm = 9,
	R_Forearm = 10,
	R_Hand = 11,
	Anim_Attachment_RH = 12,
	L_Clavicle = 13,
	L_UpperArm = 14,
	L_Forearm = 15,
	L_Hand = 16,
	Anim_Attachment_LH = 17,
	R_Thigh = 18,
	R_Calf = 19,
	R_Foot = 20,
	R_Toe0 = 21,
	L_Thigh = 22,
	L_Calf = 23,
	L_Foot = 24,
	L_Toe0 = 25,
	L_Finger4 = 26,
	L_Finger41 = 27,
	L_Finger42 = 28,
	L_Finger3 = 29,
	L_Finger31 = 30,
	L_Finger32 = 31,
	L_Finger2 = 32,
	L_Finger21 = 33,
	L_Finger22 = 34,
	L_Finger1 = 35,
	L_Finger11 = 36,
	L_Finger12 = 37,
	L_Finger0 = 38,
	L_Finger01 = 39,
	L_Finger02 = 40,
	R_Finger4 = 41,
	R_Finger41 = 42,
	R_Finger42 = 43,
	R_Finger3 = 44,
	R_Finger31 = 45,
	R_Finger32 = 46,
	R_Finger2 = 47,
	R_Finger21 = 48,
	R_Finger22 = 49,
	R_Finger1 = 50,
	R_Finger11 = 51,
	R_Finger12 = 52,
	R_Finger0 = 53,
	R_Finger01 = 54,
	R_Finger02 = 55,
	L_Elbow = 56,
	L_Ulna = 57,
	R_Ulna = 58,
	L_Pectoral = 59,
	R_Shoulder = 60,
	L_Shoulder = 61,
	R_Trapezius = 62,
	R_Wrist = 63,
	R_Bicep = 64,
	L_Bicep = 65,
	L_Trapezius = 66,
	L_Wrist = 67,
	R_Elbow = 68
};

struct bone_w2s {
	Vector2 Pelvis;
	Vector2 Spine;
	Vector2 Spine1;
	Vector2 Spine2;
	Vector2 Spine4;
	Vector2 Neck1;
	Vector2 Head1;
	Vector2 forward;
	Vector2 R_Clavicle;
	Vector2 R_UpperArm;
	Vector2 R_Forearm;
	Vector2 R_Hand;
	Vector2 Anim_Attachment_RH;
	Vector2 L_Clavicle;
	Vector2 L_UpperArm;
	Vector2 L_Forearm;
	Vector2 L_Hand;
	Vector2 Anim_Attachment_LH;
	Vector2 R_Thigh;
	Vector2 R_Calf;
	Vector2 R_Foot;
	Vector2 R_Toe0;
	Vector2 L_Thigh;
	Vector2 L_Calf;
	Vector2 L_Foot;
	Vector2 L_Toe0;
	Vector2 L_Finger4;
	Vector2 L_Finger41;
	Vector2 L_Finger42;
	Vector2 L_Finger3;
	Vector2 L_Finger31;
	Vector2 L_Finger32;
	Vector2 L_Finger2;
	Vector2 L_Finger21;
	Vector2 L_Finger22;
	Vector2 L_Finger1;
	Vector2 L_Finger11;
	Vector2 L_Finger12;
	Vector2 L_Finger0;
	Vector2 L_Finger01;
	Vector2 L_Finger02;
	Vector2 R_Finger4;
	Vector2 R_Finger41;
	Vector2 R_Finger42;
	Vector2 R_Finger3;
	Vector2 R_Finger31;
	Vector2 R_Finger32;
	Vector2 R_Finger2;
	Vector2 R_Finger21;
	Vector2 R_Finger22;
	Vector2 R_Finger1;
	Vector2 R_Finger11;
	Vector2 R_Finger12;
	Vector2 R_Finger0;
	Vector2 R_Finger01;
	Vector2 R_Finger02;
	Vector2 L_Elbow;
	Vector2 L_Ulna;
	Vector2 R_Ulna;
	Vector2 L_Pectoral;
	Vector2 R_Shoulder;
	Vector2 L_Shoulder;
	Vector2 R_Trapezius;
	Vector2 R_Wrist;
	Vector2 R_Bicep;
	Vector2 L_Bicep;
	Vector2 L_Trapezius;
	Vector2 L_Wrist;
	Vector2 R_Elbow;
};