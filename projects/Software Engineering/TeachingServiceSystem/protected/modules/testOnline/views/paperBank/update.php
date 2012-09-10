<?php
// the breadcrumbs list
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('index'),
		'Update Unpublished Paper',
);

// the menu list
$this->menu=array(
	array('label'=>'List Papers', 'url'=>array('index')),
	array('label'=>'View PaperBank', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage PaperBank', 'url'=>array('admin')),
);
?>

<h1>Update Paper Information <?php //echo $model->id; ?></h1>

<?php //echo $this->renderPartial('_form', array('model'=>$model)); ?>

<!-- the paper information form -->
<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'paper-bank-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>

	<!-- the is_publish row -->
	<div class="row">
		<?php echo $form->labelEx($model,'is_publish'); ?>
		<?php echo $form->dropDownList($model, 'is_publish', $model->getPublishOptions()); //textField($model,'is_publish'); ?>
		<?php echo $form->error($model,'is_publish'); ?>
	</div>

	<!-- the timelimit row -->
	<div class="row">
		<?php echo $form->labelEx($model,'timelimit'); ?>
		<?php 
			$this->widget('ext.timepicker.EJuiDateTimePicker',array(
			    'model'=>$model,
			    'attribute'=>'timelimit',
			    'options'=>array(
			        'hourGrid' => 1,
			    	'minGrid'=>10,
			        'hourMin' => 0,
			        'hourMax' => 2,
			        'timeFormat' => 'h:m:s',
			        ),
			    ));  
		?>
		<?php echo $form->error($model,'timelimit'); ?>
	</div>

	<!-- the submit button -->
	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div>