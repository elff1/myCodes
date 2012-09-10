<?php
//顶部的导航条
$this->breadcrumbs=array(
	InformationManagementModule::t('program','Program')=>array('index'),
	InformationManagementModule::t('program','Batch Create'),
);


//右侧导航菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('program','List Program'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('program','Manage Program'), 'url'=>array('admin')),
);
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('program', 'Batch Create Program')); ?></h1>



<!--提交文件的表单-->
<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'program-batch-form-batchCreate-form',
	'enableAjaxValidation'=>false,
	//'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<!--提示信息-->
	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<!--提示信息-->
	<p class="note"><?php echo CHtml::encode(InformationManagementModule::t('other',
	'Input format: csv, UTF-8 encoded, with format "name, department_id, length, year, introduction" per line (introduction can have multiple lines, by enclosing it in double quotes), leading & trailing whitespace ignored.')); ?></p>
	
	<?php $this->widget('zii.widgets.grid.CGridView', array(
	'dataProvider'=>$departmentDataProvider,
	'columns'=>array(
	//since not active data provider, model name have to be searched 
        array(
         'name'=>'id',
          'header'=>Department::model()->getAttributeLabel('id')
        ),
        array(
         'name'=>'name',
          //'header'=>Department::model()->getAttributeLabel('name')
		  'header'=>InformationManagementModule::t('program','Name')
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
		<?php echo CHtml::submitButton(InformationManagementModule::t('other','Submit')); 
		 ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->