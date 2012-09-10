<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Question Banks'=>array('index'),
		'batchCreate',
);

$this->menu=array(
	array('label'=>TestOnlineModule::t('core','List Questions'), 'url'=>array('index')),
	array('label'=>TestOnlineModule::t('core','Add Question'), 'url'=>array('create')),
	array('label'=>TestOnlineModule::t('core','Manage Questions'), 'url'=>array('admin')),
//	array('label'=>TestOnlineModule::t('core','Batch Add Questions'), 'url'=>array('batchCreate')),
);
?>
<div id="content">
		
<h1>Batch Create Info</h1>

<div class="form">
 
<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'question-batch-form-batchCreate-form',
	'enableAjaxValidation'=>false,
	'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<p class="note"><?php
	echo TestOnlineModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<p class="note"><?php echo CHtml::encode( TestOnlineModule::t('other',
	'Input format: csv, UTF-8 encoded, with format "questionContent, type, selectionA, selectionB,selectionC,selectionD,answer" per line.')); ?></p>
	
	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'file'); ?>
		<?php echo $form->fileField($model,'file'); ?>
		<?php echo $form->error($model,'file'); ?>
	</div>


	<div class="row buttons">
		<?php echo CHtml::submitButton(Yii::t('base','Submit')); 
		 ?>
	</div>

<?php $this->endWidget(); ?>

</div>

</div>

