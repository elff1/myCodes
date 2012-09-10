<?php
//顶部的导航条
$this->breadcrumbs=array(
	InformationManagementModule::t('department','Departments')=>array('index'),
	InformationManagementModule::t('department','Batch Create Department'),
);


//右侧导航菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('department','List Department'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('department','Manage Department'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('department', 'Batch Create Department')); ?></h1>


<!--提交文件的表单-->
<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'department-batch-form-batchCreate-form',
	'enableAjaxValidation'=>false,
	'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<!--提示信息-->
	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<!--提示信息-->
	<p class="note"><?php echo CHtml::encode(InformationManagementModule::t('other',
	'Input format: csv, UTF-8 encoded, with one name of department per line, leading & trailing whitespace ignored.')); ?></p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'file'); ?>
		<?php echo $form->fileField($model,'file'); ?>
		<?php echo $form->error($model,'file'); ?>
	</div>


	<!--提交按钮-->
	<div class="row buttons">
		<?php echo CHtml::submitButton(Yii::t('base','Submit')); 
		 ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->