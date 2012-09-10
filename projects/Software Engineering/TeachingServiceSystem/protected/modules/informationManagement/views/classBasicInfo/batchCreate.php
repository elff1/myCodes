<?php
//顶部的导航条
$this->breadcrumbs=array(
	InformationManagementModule::t('classBasicInfo', 'Manage ClassBasicInfo')=>array('index'),
	InformationManagementModule::t('classBasicInfo', 'Batch Create Class'),
);


//右侧导航菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('classBasicInfo', 'Create ClassBasicInfo'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('classBasicInfo', 'List ClassBasicInfo'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('classBasicInfo', 'Manage ClassBasicInfo'), 'url'=>array('admin')),
	//array('label'=>Yii::t('classBasicInfo','Batch Create Class'), 'url'=>array('batchCreate')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('classBasicInfo', 'Batch Create Class')); ?></h1>


<!--提交文件的表单-->
<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'classBasicInfo-batch-form-batchCreate-form',
	'enableAjaxValidation'=>false,
	'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<!--提示信息-->
	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<!--提示信息-->
	<p class="note"><?php echo CHtml::encode(InformationManagementModule::t('other',
	'Input format: csv, UTF-8 encoded, with format "name, grade, tutor_id" per line, leading & trailing whitespace ignored.')); ?></p>
	
	<?php $this->widget('zii.widgets.grid.CGridView', array(
	'dataProvider'=>$classBasicInfoDataProvider,
	'columns'=>array(
	//since not active data provider, model name have to be searched 
        array(
         'name'=>'name',
          'header'=>InformationManagementModule::t('classBasicInfo','Class Name'),
        ),
        array(
         'name'=>'grade',
          'header'=>InformationManagementModule::t('classBasicInfo','Grade'),
        ),
		 array(
         'name'=>'tutor_id',
          'header'=>InformationManagementModule::t('classBasicInfo','Tutor'),
        ),
    	),
	)); ?>
	
	
	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'file'); ?>
		<?php echo $form->fileField($model,'file'); ?>
		<?php echo $form->error($model,'file'); ?>
	</div>


	<!--提交按钮-->
	<div class="row buttons">
		<?php echo CHtml::submitButton(InformationManagementModule::t('other', 'Submit')); 
		 ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->